#include "bloc.h"

static struct super_s super;
static unsigned int current_vol;

void init_super(unsigned int vol) {
  struct freeBloc_s fb;

  super.super_magic = SUPERMAGIC;
  super.super_firstFree = 1;
  super.super_nFree = mbr.mbr_vols[current_vol].vol_nSector - 1;
  super.super_root = 0;

  save_super();

  fb.fb_nblocs = mbr.mbr_vols[current_vol].vol_nSector - 1;
  fb.fb_next = 0;

  write_bloc(current_vol, 0, (unsigned char *) &fb);
}

int load_super(unsigned int vol) {
  current_vol = vol;
  read_bloc(current_vol, vol, (unsigned char *) &super);

  return super.super_magic == SUPERMAGIC;
}

void save_super() {
  write_bloc(current_vol, 0, (unsigned char *) &super);
}

unsigned int new_bloc() {
  struct freeBloc_s fb;
  unsigned int freeBloc;
  if(super.super_nFree == 0)
    return 0; /*Volume plein*/

  freeBloc = super.super_firstFree;
  super.super_nFree--;
  read_bloc(current_vol, super.super_firstFree, (unsigned char *) &fb);

  if(fb.fb_nblocs > 1) {
    super.super_firstFree++;
    fb.fb_nblocs--;
    write_bloc(current_vol, super.super_firstFree, (unsigned char *) &fb);
  } else {
    super.super_firstFree = fb.fb_next;
  }
  save_super();
  return freeBloc;
}

void free_bloc (unsigned int bloc) {
  struct freeBloc_s fb;

  fb.fb_next = super.super_firstFree;
  fb.fb_nblocs = 1;

  write_bloc(current_vol, bloc, (unsigned char *) &fb);

  super.super_firstFree = bloc;
}

void read_bloc_n(unsigned int nBloc, unsigned char * buffer, unsigned int size){
  read_sector_n(cylinder_of_bloc(current_vol, nBloc), sector_of_bloc(current_vol, nBloc), buffer, size);
}

void write_bloc_n(unsigned int nBloc, unsigned char * buffer, unsigned int size){
  write_sector_n(cylinder_of_bloc(current_vol, nBloc), sector_of_bloc(current_vol, nBloc), buffer, size);
}

void read_inode(unsigned int inumber, struct inode_s inode){
  read_bloc_n(inumber, &inode, sizeof(struct inode_s));
}

void write_inode(unsigned int inumber, struct inode_s inode){
  write_bloc_n(inumber, &inode, sizeof(struct inode_s));
}

unsigned int create_inode(enum file_type_e type){
  struct inode_s inode;
  unsigned int bloc;
  inode.i_type = type;
  inode.i_size = 0;
  for(int i = 0; i < NDIRECT; i++)
    inode.i_direct[i] = 0;
  inode.i_indirect = 0;
  inode.i_2indirect = 0;
  bloc = new_bloc();
  write_inode(bloc, &inode);

  return bloc;
}

void free_blocs(unsigned int blocs[], unsigned int size){
    for(int i = 0; i < size; i++)
      if(blocs[i])
        free_bloc(blocs[i]);
}

void delete_inode(unsigned int inumber){
    struct inode_s inode;
    read_inode(inumber, &inode);

    free_blocs(inode.i_direct, NDIRECT);
    if(inode.i_indirect){
      unsigned int bloc[NNBPB];
      read_bloc_n(inode.i_indirect, bloc, sizeof(unsigned int));
      free_blocs(bloc, NNBPB);
      free_bloc(inode.inode_indirect);
    }

    if(inode.i_2indirect){
      unsigned int bloc2[NNBPB];
      read_bloc_n(inode.i_2indirect, bloc2, sizeof(unsigned int));
      for(int b = 0; b < NNBPB; b++){
        if(bloc2[b]){
          unsigned int bloc[NNBPB];
          read_bloc_n(bloc2[b], bloc, sizeof(unsigned int));
          free_blocs(bloc, NNBPB);
          free_bloc(bloc2[b]);
        }
      }
      free_bloc(inode.i_2indirect);
    }
    free_bloc(inumber);
}

unsigned int vbloc_of_fbloc(unsigned int inumber, unsigned int fbloc) {
  struct inode_s inode;
  read_inode(inumber, &inode);
  if(fbloc < NDIRECT)
    return inode.i_direct[fbloc];
}
