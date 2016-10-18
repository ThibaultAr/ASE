#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hardware.h"

#define SECTORSIZE 256
#define HDA_CMDREG 0x3F6
#define HDA_DATAREGS 0x110
#define HDA_IRQ 14

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);

void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char *buffer);

void format_sector(unsigned int cylinder, unsigned int sector, unsigned int nsector, unsigned int value);

void check_dskinfo(unsigned int cylinder, unsigned int sector);