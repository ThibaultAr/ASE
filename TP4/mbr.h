#ifndef MBR_H_
#define MBR_H_

#include "drive.h"

#define MAX_VOLUMES 5
#define MBR_MAGIC 0xC0DEBEEF

enum vol_type_e {VOL_BASIC, VOL_ANX, VOL_OTHER};

extern struct mbr_s mbr;

struct volume_s {
  unsigned int vol_first_sector;
  unsigned int vol_first_cylinder;
  unsigned int vol_nSector;
  enum vol_type_e vol_type;
};

struct mbr_s {
  unsigned int mbr_dirty;
  struct volume_s mbr_vols [MAX_VOLUMES];
  unsigned int mbr_nVol;
  unsigned int mbr_magic;
};

#define load_mbr read_mbr

int read_mbr();

void write_mbr();

void read_bloc(int numVol, int numBloc, unsigned char *buffer);

void read_bloc_n(int numVol, int numBloc, unsigned char *buffer, int size);

void write_bloc(int numVol, int numBloc, unsigned char *buffer);

void write_bloc_n(int numVol, int numBloc, unsigned char *buffer, int size);

int sector_of_bloc(int numVol, int numBloc);

int cylinder_of_bloc(int numVol, int numBloc);

#endif
