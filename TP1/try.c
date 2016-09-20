#include "try.h"
#include <assert.h>

int try (struct ctx_s * pctx, func_t *f, int arg) {
  asm("movl %%esp, %0"
        : "=r" (pctx->ctx_esp));
  asm("movl %%ebp, %0"
        : "=r" (pctx->ctx_ebp));
  pctx->ctx_magic = CTX_MAGIC;
  return f(arg);
}

int throw (struct ctx_s * pctx, int val) {
  static int throw_r;
  assert (pctx->ctx_magic == CTX_MAGIC);
  throw_r = val;
  asm("movl %0, %%esp"
        :
        : "r" (pctx->ctx_esp));
  asm("movl %0, %%ebp"
        :
        : "r" (pctx->ctx_ebp));
  return throw_r;
}
