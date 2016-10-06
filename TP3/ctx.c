#include "ctx.h"

static struct ctx_s * cctx = (struct ctx_s *) 0;
static void * main_esp;
static void * main_ebp;

int init_ctx (struct ctx_s * ctx, int stack_size, func_t * f, void * args) {
  ctx->ctx_magic = CTX_MAGIC;
  ctx->ctx_f = f;
  ctx->ctx_args = args;
  ctx->ctx_state = CTX_INIT;
  assert(ctx->ctx_stack = malloc(stack_size));
  ctx->ctx_esp = ctx->ctx_stack + stack_size - 4;
  ctx->ctx_ebp = ctx->ctx_stack + stack_size - 4;

  return 0;
}

int create_ctx(int stack_size, func_t * f, void * args){
  struct ctx_s * ctx = malloc (sizeof(struct ctx_s));
  if(!ring_ctx){
    ring_ctx = ctx;
    ctx->ctx_next = ctx;
  } else {
    ctx->ctx_next = ring_ctx->ctx_next;
    ring_ctx->ctx_next = ctx;
  }
  init_ctx(ctx, stack_size, f, args);
  return 0;
}

void yield () {
  if(!ring_ctx)
    return;
  if(!cctx)
    switch_to_ctx(ring_ctx);
  else
    switch_to_ctx(cctx->ctx_next);
}

void start_current_ctx () {
  cctx->ctx_state = CTX_EXEC;
  cctx->ctx_f(cctx->ctx_args);

  cctx->ctx_state = CTX_END;
  yield();
}

void switch_to_ctx (struct ctx_s * ctx) {
  assert(ctx->ctx_magic == CTX_MAGIC);
  while(ctx->ctx_state == CTX_END) {
    free(ctx->ctx_stack);
    if(ctx->ctx_next == ctx) {
      ring_ctx = NULL;
      free(ctx);
      asm("movl %0, %%esp"
          :
          : "r" (main_esp));
      asm("movl %0, %%ebp"
          :
          : "r" (main_ebp));
      return;
    } else {
      printf("\nA process has ended\n");
      cctx->ctx_next = ctx->ctx_next;
      if(ring_ctx == ctx)
        ring_ctx = ctx->ctx_next;
      free(ctx);
      ctx = cctx;
    }
  }

  if(cctx) {
    asm("movl %%esp, %0"
       : "=r" (cctx->ctx_esp));
    asm("movl %%ebp, %0"
       : "=r" (cctx->ctx_ebp));
  } else {
    asm("movl %%esp, %0"
       : "=r" (main_esp));
    asm("movl %%ebp, %0"
       : "=r" (main_ebp));
  }
  cctx = ctx;
  asm("movl %0, %%esp"
      :
      : "r" (cctx->ctx_esp));
  asm("movl %0, %%ebp"
      :
      : "r" (cctx->ctx_ebp));

  if(cctx->ctx_state == CTX_INIT)
    start_current_ctx();
  return;
}
