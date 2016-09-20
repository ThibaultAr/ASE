#define CTX_MAGIC 0xDEADBEEF

struct ctx_s {
  void * ctx_esp;
  void * ctx_ebp;
  unsigned ctx_magic;
};

typedef int (func_t) (int);

int try (struct ctx_s * pctx, func_t * f, int arg);

int throw (struct ctx_s * pctx, int val);
