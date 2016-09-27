#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
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
}

void start_current_ctx () {
  cctx->ctx_state = CTX_EXEC;
  cctx->ctx_f(cctx->ctx_args);

  cctx->ctx_state = CTX_END;
  printf("\na process has ended\n");
  asm("movl %0, %%esp"
      :
      : "r" (main_esp));
  asm("movl %0, %%ebp"
      :
      : "r" (main_ebp));
}

void switch_to_ctx (struct ctx_s * ctx) {
  assert(ctx->ctx_magic == CTX_MAGIC);
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
