#include "bloc.h"

static struct super_s super;
static unsigned int current_vol;

void init_super(unsigned int vol) {
  struct freeBloc_s fb;

  super.super_magic = SUPERMAGIC;
  super.super_firstFree = 1;
  super.super_nFree = mbr.mbr_vols[vol].vol_nSector - 1;
  super.super_root = 0;

  save_super();

  fb.fb_nblocs = mbr.mbr_vols[vol].vol_nSector - 1;
  fb.fb_next = 0;

  write_bloc_n(vol, 0, (unsigned char *) &fb, sizeof(struct freeBloc_s));
}

int load_super(unsigned int vol) {
  current_vol = vol;
  read_bloc_n(current_vol, 0, (unsigned char *) &super, sizeof(struct super_s));

  return super.super_magic == SUPERMAGIC;
}

void save_super() {
  write_bloc_n(current_vol, 0, (unsigned char *) &super, sizeof(struct super_s));
}

unsigned int new_bloc() {
  struct freeBloc_s fb;
  unsigned int freeBloc;
  if(super.super_nFree == 0)
    return 0; /*Volume plein*/

  freeBloc = super.super_firstFree;
  super.super_nFree--;
  read_bloc_n(current_vol, super.super_firstFree, (unsigned char *) &fb, sizeof(struct freeBloc_s));

  if(fb.fb_nblocs > 1) {
    super.super_firstFree++;
    fb.fb_nblocs--;
    write_bloc_n(current_vol, super.super_firstFree, (unsigned char *) &fb, sizeof(struct freeBloc_s));
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

  write_bloc_n(current_vol, bloc, (unsigned char *) &fb, sizeof(struct freeBloc_s));

  super.super_firstFree = bloc;
}
