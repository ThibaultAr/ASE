/* ------------------------------
   $Id: mkhd.c,v 1.4 2004/10/12 09:16:57 marquet Exp $
   ------------------------------------------------------------

   Create and intialize a drive using the hardware simulator.
   Philippe Marquet, october 2002

   A minimal example of a program using the ATA interface.
   It is given to the students as such.

*/

#include <stdlib.h>
#include <stdio.h>
#include "hardware.h"
#include "drive.h"
#include "dump.c"

static void empty_it() {
  return;
}

void dmps (unsigned int cylinder, unsigned int sector) {
  unsigned char buffer[SECTORSIZE];
  check_dskinfo(cylinder, sector);
  read_sector(cylinder, sector, buffer);
  dump(buffer, SECTORSIZE, 0, 1);
}

void frmt(unsigned int value) {
    int i;
    check_dskinfo(0, 0);
    for(i = 0; i < CYLINDERS; i++) {
      format_sector(i, 0, SECTORS, value);
    }
}

int main(int argc, char **argv) {
  unsigned int i, j;

  /* init hardware */
  if(init_hardware("hardware.ini") == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }

  /* Interreupt handlers */
  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);

  frmt(0);
  for(i = 0; i < CYLINDERS; i++) {
    for(j = 0; j < SECTORS; j++) {
      dmps(i, j);
    }
  }

  /* and exit! */
  exit(EXIT_SUCCESS);
}
