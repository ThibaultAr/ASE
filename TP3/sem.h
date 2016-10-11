#include "ctx.h"

struct sem_s {
  int sem_cpt;
  struct ctx_s * sem_ctx;
};

void sem_init(struct sem_s * sem, unsigned int value);

void sem_down (struct sem_s * sem);

void sem_up (struct sem_s * sem);
