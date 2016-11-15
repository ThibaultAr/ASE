#define SUPERMAGIC 0xFE55E
#define SUPER 0
#define NDIRECT 10

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

enum file_type_e {DIR, FILE_FILE};

struct inode_s {
  enum file_type_e i_type;
  unsigned int i_size;
  unsigned int i_direct[NDIRECT];
  unsigned int i_indirect;
  unsigned int i_2indirect;
}

void init_super(unsigned int vol);

int load_super(unsigned int vol);

void save_super();

unsigned int new_bloc();

void free_bloc (unsigned int bloc);
