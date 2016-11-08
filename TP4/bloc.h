#define SUPERMAGIC 0xFE55E
#define SUPER 0

#include "mbr.h"

struct super_s {
  unsigned int super_magic;
  unsigned int super_firstFree;
  unsigned int super_nFree;
  unsigned int super_root;
};

struct freeBloc_s {
  unsigned int fb_nblocs;
  unsigned int fb_next;
};

void init_super(unsigned int vol);

int load_super(unsigned int vol);

void save_super();

unsigned int new_bloc();

void free_bloc (unsigned int bloc);
