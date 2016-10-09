#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "hardware.h"

#define CTX_MAGIC 0xBADC0DE

#ifndef _HW_CONFIG_H_
#define _HW_CONFIG_H_

#define HARDWARE_INI	"hardware.ini"

/* Horloge */
#define TIMER_CLOCK	0xF0
#define TIMER_PARAM     0xF4
#define TIMER_ALARM     0xF8
#define TIMER_IRQ	2

#endif

typedef void (func_t) (void *);

enum ctx_state_e {CTX_INIT, CTX_EXEC, CTX_END};

struct ctx_s {
  unsigned ctx_magic;
  void * ctx_esp;
  void * ctx_ebp;
  func_t * ctx_f;
  void * ctx_args;
  enum ctx_state_e ctx_state;
  char * ctx_stack;
  struct ctx_s * ctx_next;
};

static struct ctx_s * ring_ctx = NULL;

void start_schedule();

void yield ();

int create_ctx(int stack_size, func_t * f, void * args);

int init_ctx (struct ctx_s * ctx, int stack_size, func_t * f, void * args);

void switch_to_ctx (struct ctx_s * ctx);
