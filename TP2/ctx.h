#define CTX_MAGIC 0xBADC0DE

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
};

int init_ctx (struct ctx_s * ctx, int stack_size, func_t * f, void * args);

void switch_to_ctx (struct ctx_s * ctx);
