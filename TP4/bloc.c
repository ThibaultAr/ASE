#include "bloc.h"

struct super_s super;

void init_super() {
  struct freeBloc_s fb;

  super.super_magic = SUPERMAGIC;
  super.super_firstFree = 1;
  super.super_nFree = mbr.mbr_vols[current_volume].vol_nSector - 1;
  super.super_root = 0;

  save_super();

  fb.fb_nblocs = mbr.mbr_vols[current_volume].vol_nSector - 1;
  fb.fb_next = 0;

  write_bloc_n(current_volume, 1, (unsigned char *) &fb, sizeof(struct freeBloc_s));
}

int load_super(unsigned int vol) {
  current_volume = vol;
  read_bloc_n(current_volume, 0, (unsigned char *) &super, sizeof(struct super_s));

  return super.super_magic == SUPERMAGIC;
}

void save_super() {
  write_bloc_n(current_volume, 0, (unsigned char *) &super, sizeof(struct super_s));
}

unsigned int new_bloc() {
  struct freeBloc_s fb;
  unsigned int freeBloc;
  if(super.super_nFree == 0)
    return 0; /*Volume plein*/

  freeBloc = super.super_firstFree;
  super.super_nFree--;
  read_bloc_n(current_volume, super.super_firstFree, (unsigned char *) &fb, sizeof(struct freeBloc_s));

  if(fb.fb_nblocs > 1) {
    super.super_firstFree++;
    fb.fb_nblocs--;
    write_bloc_n(current_volume, super.super_firstFree, (unsigned char *) &fb, sizeof(struct freeBloc_s));
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

  write_bloc_n(current_volume, bloc, (unsigned char *) &fb, sizeof(struct freeBloc_s));

  super.super_firstFree = bloc;
  super.super_nFree++;
}

void read_inode(unsigned int inumber, struct inode_s * inode){
  read_bloc_n(current_volume, inumber, (unsigned char *) inode, sizeof(struct inode_s));
}

void write_inode(unsigned int inumber, struct inode_s * inode){
  write_bloc_n(current_volume, inumber, (unsigned char *) inode, sizeof(struct inode_s));
}

unsigned int create_inode(enum file_type_e type){
  struct inode_s inode;
  unsigned int bloc;
  int i;
  inode.i_type = type;
  inode.i_size = 0;
  for(i = 0; i < NDIRECT; i++)
    inode.i_direct[i] = 0;
  inode.i_indirect = 0;
  inode.i_2indirect = 0;
  bloc = new_bloc();
  write_inode(bloc, &inode);

  return bloc;
}

void free_blocs(unsigned int blocs[], unsigned int size){
    int i;
    for(i = 0; i < size; i++)
      if(blocs[i])
        free_bloc(blocs[i]);
}

int delete_inode(unsigned int inumber){
  struct inode_s inode;
  read_inode(inumber, &inode);

  free_blocs(inode.i_direct, NDIRECT);
  if(inode.i_indirect){
    unsigned int bloc[NNBPB];
    read_bloc_n(current_volume, inode.i_indirect, (unsigned char *) bloc, sizeof(unsigned int));
    free_blocs(bloc, NNBPB);
    free_bloc(inode.i_indirect);
  }

  if(inode.i_2indirect){
    unsigned int bloc2[NNBPB];
    int b;
    read_bloc_n(current_volume, inode.i_2indirect, (unsigned char *) bloc2, sizeof(unsigned int));
    for(b = 0; b < NNBPB; b++){
      if(bloc2[b]){
        unsigned int bloc[NNBPB];
        read_bloc_n(current_volume, bloc2[b], (unsigned char *) bloc, sizeof(unsigned int));
        free_blocs(bloc, NNBPB);
        free_bloc(bloc2[b]);
      }
    }
    free_bloc(inode.i_2indirect);
  }
  free_bloc(inumber);
  return 0;
}

unsigned int new_bloc_zero() {
  int bloc = new_bloc();
  format_bloc(current_volume, bloc);
  return bloc;
}

unsigned int vbloc_of_fbloc(unsigned int inumber, unsigned int fbloc, int do_allocate) {
  struct inode_s inode;
  read_inode(inumber, &inode);
  /* Direct */
  if(fbloc < NDIRECT) {
    if(do_allocate && !inode.i_direct[fbloc]) {
      unsigned int newBlock = new_bloc_zero();
      if(newBlock != 0) {
        inode.i_direct[fbloc] = newBlock;
        write_inode(inumber, &inode);
      }
    }
    return inode.i_direct[fbloc];
  }

  /* Indirect */
  fbloc -= NDIRECT;

  if(fbloc < NNBPB) {
    unsigned int bloc[NNBPB];
    if(do_allocate && !inode.i_indirect) {
      int i;
      unsigned int newBlock = new_bloc_zero();
      if(newBlock != 0) {
        inode.i_indirect = newBlock;
        for(i = 0; i < NNBPB; i++) {
          unsigned int newBlock1 = new_bloc_zero();
          if(newBlock1 != 0) {
            bloc[i] = newBlock1;
          }
        }
        write_bloc_n(current_volume, inode.i_indirect, (unsigned char *) bloc, sizeof(unsigned int));
        write_inode(inumber, &inode);
      } else {
        return 0;
      }
    }
    read_bloc_n(current_volume, inode.i_indirect, bloc, sizeof(unsigned int));
    return bloc[fbloc];
  }

  /* Double indirect */
  fbloc -= NNBPB;

  if(fbloc < NNBPB * NNBPB) {
    unsigned int bloc[NNBPB], bloc1[NNBPB];
    if(do_allocate && !inode.i_2indirect) {
      unsigned int newBlock = new_bloc_zero();
      if(newBlock != 0) {
        int i, j;
        inode.i_2indirect = newBlock;
        for(i = 0; i < NNBPB; i++) {
          unsigned int newBlock1 = new_bloc_zero();
          if(newBlock1 != 0) {
            for(j = 0; j < NNBPB; j++) {
              unsigned int newBlock2 = new_bloc_zero();
              if(newBlock2 != 0) {
                bloc1[j] = newBlock2;
              }
            }
            write_bloc_n(current_volume, bloc[i], (unsigned char *) bloc1, sizeof(unsigned int));
          }
        }
        write_bloc_n(current_volume, inode.i_2indirect, (unsigned char *) bloc, sizeof(unsigned int));
        write_inode(inumber, &inode);
      } else {
        return 0;
      }
    }
    read_bloc_n(current_volume, inode.i_2indirect, bloc, sizeof(unsigned int));
    if(bloc[fbloc / NNBPB] == 0) return 0;
    read_bloc_n(current_volume, bloc[fbloc / NNBPB], bloc1, sizeof(unsigned int));
    if(bloc[fbloc % NNBPB] == 0) return 0;
    return bloc[fbloc % NNBPB];
  }

  printf("Fichier trop grand\n");
  exit(1);
}
