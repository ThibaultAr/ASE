#include "mbr.h"

struct mbr_s mbr;

int read_mbr() {
  read_sector_n(0, 0, (unsigned char *) &mbr, sizeof(struct mbr_s));
  if(mbr.mbr_magic != MBR_MAGIC) {
    mbr.mbr_magic = MBR_MAGIC;
    mbr.mbr_nVol = 0;
    return 0;
  }
  return 1;
}

void write_mbr() {
  write_sector_n(0, 0, (unsigned char *) &mbr, sizeof(struct mbr_s));
}

unsigned int sector_of_bloc(unsigned int numVol, unsigned int numBloc) {
  if(numVol > mbr.mbr_nVol) {
    printf("Volume inexistant\n");
    exit(1);
  }
  if(numBloc > mbr.mbr_vols[numVol].vol_nSector) {
    printf("Depassement du volume\n");
    exit(1);
  }
  return (mbr.mbr_vols[numVol].vol_first_sector + numBloc) % SECTORS;
}

unsigned int cylinder_of_bloc(unsigned int numVol, unsigned int numBloc) {
  if(numVol > mbr.mbr_nVol) {
    printf("Volume inexistant\n");
    exit(1);
  }
  if(numBloc > mbr.mbr_vols[numVol].vol_nSector) {
    printf("Depassement du volume\n");
    exit(1);
  }
  return mbr.mbr_vols[numVol].vol_first_cylinder + (mbr.mbr_vols[numVol].vol_first_sector + numBloc) / SECTORS;
}

void read_bloc(unsigned int numVol, unsigned int numBloc, unsigned char *buffer) {
  read_sector(cylinder_of_bloc(numVol, numBloc), sector_of_bloc(numVol, numBloc), buffer);
}

void read_bloc_n(unsigned int numVol, unsigned int numBloc, unsigned char *buffer, int size) {
  read_sector_n(cylinder_of_bloc(numVol, numBloc), sector_of_bloc(numVol, numBloc), buffer, size);
}

void write_bloc(unsigned int numVol, unsigned int numBloc, unsigned char *buffer) {
  write_sector(cylinder_of_bloc(numVol, numBloc), sector_of_bloc(numVol, numBloc), buffer);
}

void write_bloc_n(unsigned int numVol, unsigned int numBloc, unsigned char *buffer, int size) {
  write_sector_n(cylinder_of_bloc(numVol, numBloc), sector_of_bloc(numVol, numBloc), buffer, size);
}

void format_bloc(unsigned int numVol, unsigned int numBloc) {
  format_sector(cylinder_of_bloc(numVol, numBloc), sector_of_bloc(numVol, numBloc), 1, 0);
}
