#include "mbr.h"

int main(int argc, char const *argv[]) {
  struct volume_s vol;
  int i;

  read_mbr();
  for(i = 1; i < argc; i+=2) {
      if(argv[i] == "-s")
        vol.vol_nSector = atoi(argv[i+1]);
      else if(argv[i] == "-fc")
        vol.vol_first_cylinder = atoi(argv[i+1]);
      else if(argv[i] == "-fs")
        vol.vol_first_sector = atoi(argv[i+1]);
      else {
        printf("Invalid option\n");
        exit(1);
      }
  }
  vol.vol_type = VOL_BASIC;
  mbr.mbr_vols[mbr.mbr_nVol++] = vol;

  write_mbr();

  return 0;
}
