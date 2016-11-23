#ifndef BLOCK_H_
#define BLOCK_H_

#define SUPERMAGIC 0xFE55E
#define SUPER 0
#define NDIRECT 10
#define NNBPB 2
#define DATA_BLOC_SIZE 256
#define BLOC_SIZE DATA_BLOC_SIZE

#include "mbr.h"

extern unsigned int current_volume;

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

enum file_type_e {FILE_FILE, FILE_DIRECTORY, FILE_SPECIAL};

struct inode_s {
  enum file_type_e i_type;
  unsigned int i_size;
  unsigned int i_direct[NDIRECT];
  unsigned int i_indirect;
  unsigned int i_2indirect;
};

void init_super();

int load_super(unsigned int vol);

void save_super();

unsigned int new_bloc();

void free_bloc (unsigned int bloc);

/* inodes i/o */
void read_inode (unsigned int inumber, struct inode_s *inode);
void write_inode (unsigned int inumber, struct inode_s *inode);

/* inodes creation/deletion.
   The creation return a inumber */
unsigned int create_inode(enum file_type_e type);
int delete_inode(unsigned int inumber);

/* return the bloc index on the volume of a given bloc index in a
   file.  Return BLOC_NULL for a bloc full of zeros.
   If do_allocate, allocate blocs if needed; return BLOC_NULL if no
   allocation was possible.  */
unsigned int vbloc_of_fbloc(unsigned int inumber, unsigned int fbloc,
                            int do_allocate);
#endif
