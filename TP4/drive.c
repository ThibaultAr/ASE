#include "drive.h"

void goto_sector(unsigned int cylinder, unsigned int sector) {
  _out(HDA_DATAREGS, (cylinder >> 8) & 0xFF);
  _out(HDA_DATAREGS + 1, cylinder & 0xFF);
  _out(HDA_DATAREGS + 2, (sector >> 8) & 0xFF);
  _out(HDA_DATAREGS + 3, sector & 0xFF);
  _out(HDA_CMDREG, CMD_SEEK);
  _sleep(HDA_IRQ);
}

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer) {
  read_sector_n(cylinder, sector, buffer, SECTORSIZE);
}

void read_sector_n(unsigned int cylinder, unsigned int sector, unsigned char *buffer, unsigned int buffersize) {
  if(buffersize > SECTORSIZE){
    printf("Impossible de lire plus de %d octets sur un secteur\n", SECTORSIZE);
    exit(1);
  }
  goto_sector(cylinder, sector);
  _out(HDA_DATAREGS, 0);
  _out(HDA_DATAREGS + 1, 1);
  _out(HDA_CMDREG, CMD_READ);
  _sleep(HDA_IRQ);
  memcpy(buffer, MASTERBUFFER, buffersize);
}

void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char *buffer) {
  write_sector_n(cylinder, sector, buffer, SECTORSIZE);
}

void write_sector_n(unsigned int cylinder, unsigned int sector, const unsigned char *buffer, unsigned int buffersize) {
  goto_sector(cylinder, sector);
  memcpy(MASTERBUFFER, buffer, buffersize);
  _out(HDA_DATAREGS, 0);
  _out(HDA_DATAREGS + 1, 1);
  _out(HDA_CMDREG, CMD_WRITE);
  _sleep(HDA_IRQ);
}

void format_sector(unsigned int cylinder, unsigned int sector, unsigned int nsector, unsigned int value) {
  int i;
  goto_sector(cylinder, sector);
  _out(HDA_DATAREGS, 0);
  _out(HDA_DATAREGS + 1, 1);
  _out(HDA_DATAREGS + 2, (value >> 24) & 0xFF);
  _out(HDA_DATAREGS + 3, (value >> 16) & 0xFF);
  _out(HDA_DATAREGS + 4, (value >> 8) & 0xFF);
  _out(HDA_DATAREGS + 5, value & 0xFF);
  for(i = 0; i < nsector; i++) {
    _out(HDA_CMDREG, CMD_FORMAT);
    _sleep(HDA_IRQ);
  }
}

void check_dskinfo(unsigned int cylinder, unsigned int sector) {
  int nbCyl, nbSec, tailleSec;
  _out(HDA_CMDREG, CMD_DSKINFO);
  nbCyl = _in(HDA_DATAREGS);
  nbCyl = (nbCyl << 8) + _in(HDA_DATAREGS + 1);
  nbSec = _in(HDA_DATAREGS + 2);
  nbSec = (nbSec << 8) + _in(HDA_DATAREGS + 3);
  tailleSec = _in(HDA_DATAREGS + 4);
  tailleSec = (tailleSec << 8) + _in(HDA_DATAREGS + 5);

  if(tailleSec != SECTORSIZE) {
    printf("Recompilez le noyau avec une taille de secteur de : %d\n", tailleSec);
    exit(1);
  }

  if(cylinder >= nbCyl || cylinder > 0xFF || nbCyl != CYLINDERS) {
    printf("L'indice du cylindre est trop grand ou n'est pas sur 16 bits (indice max : %d)\n", nbCyl - 1);
    exit(1);
  }

  if(sector >= nbSec || sector > 0xFF || nbSec != SECTORS) {
    printf("L'indice du secteur est trop grand ou n'est pas sur 16 bits (indice max : %d)\n", nbSec - 1);
    exit(1);
  }
}
