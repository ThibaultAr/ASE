#include "sem.h"

void sem_init(struct sem_s * sem, unsigned int value) {
  sem->sem_cpt = value;
  sem->sem_ctx = NULL;
}

void sem_down (struct sem_s * sem) {
  irq_disable();
  sem->sem_cpt--;
  if (sem->sem_cpt < 0) {
    cctx->ctx_state = CTX_SEM;
    cctx->ctx_next_sem = sem->sem_ctx;
    sem->sem_ctx = cctx;
    irq_enable();
    yield();
  } else {
    irq_enable();
  }
}

void sem_up (struct sem_s * sem) {
  irq_disable();
  sem->sem_cpt++;
  if (sem->sem_cpt <= 0) {
    sem->sem_ctx->ctx_state = CTX_EXEC;
    sem->sem_ctx = sem->sem_ctx->ctx_next_sem;
  }
  irq_enable();
}
