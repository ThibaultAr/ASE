#include "ctx.h"

struct ctx_s * cctx = (struct ctx_s *) 0;
static struct ctx_s * ring_ctx = NULL;
static void * main_esp;
static void * main_ebp;

static void empty_it(void) {
    return;
}

static void timer_it() {
  _out(TIMER_ALARM,0xFFFFFFFE);
  yield();
}

void irq_disable() {
  _mask(TIMER_IRQ + 1);
  _out(TIMER_ALARM,0xFFFFFFFE);
}

void irq_enable() {
  _mask(1);
}

void start_schedule() {
  // Hardware initialization
  if(init_hardware(HARDWARE_INI) == 0) {
    printf("Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }

  //timer irq define
  for(int i = 0; i < 16; i++)
    IRQVECTOR[i] = empty_it;

  IRQVECTOR[TIMER_IRQ] = timer_it;

  //arm timer
  _out(TIMER_PARAM, 128 + 64 + 32 + 8); //reset + alarm on + 8 tick / alarm
  _out(TIMER_ALARM, 0xFFFFFFFE); // alarm at next tick (at 0xffffffff)

  irq_enable();

  for (int i=0; i<(1<<28); i++);
}

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
  irq_disable();
  if(!ring_ctx){
    ring_ctx = ctx;
    ctx->ctx_next = ctx;
  } else {
    ctx->ctx_next = ring_ctx->ctx_next;
    ring_ctx->ctx_next = ctx;
  }
  init_ctx(ctx, stack_size, f, args);
  irq_enable();
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
  irq_disable();
  while(ctx->ctx_state == CTX_SEM) {
    ctx = ctx->ctx_next;
  }
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
  irq_enable();
  if(cctx->ctx_state == CTX_INIT)
    start_current_ctx();
  return;
}
