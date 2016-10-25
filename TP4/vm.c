/* ------------------------------
   $Id: vm-skel.c,v 1.1 2002/10/21 07:16:29 marquet Exp $
   ------------------------------------------------------------

   Volume manager skeleton.
   Philippe Marquet, october 2002

   1- you must complete the NYI (not yet implemented) functions
   2- you may add commands (format, etc.)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mbr.h"

struct mbr_s mbr;

/* ------------------------------
   command list
   ------------------------------------------------------------*/
struct _cmd {
    char *name;
    void (*fun) (struct _cmd *c);
    char *comment;
};

static void list(struct _cmd *c);
static void new(struct _cmd *c);
static void del(struct _cmd *c);
static void help(struct _cmd *c) ;
static void save(struct _cmd *c);
static void quit(struct _cmd *c);
static void xit(struct _cmd *c);
static void none(struct _cmd *c) ;

static struct _cmd commands [] = {
    {"list", list, 	"display the partition table"},
    {"new",  new,	"create a new partition"},
    {"del",  del,	"delete a partition"},
    {"save", save,	"save the MBR"},
    {"quit", quit,	"save the MBR and quit"},
    {"exit", xit,	"exit (without saving)"},
    {"help", help,	"display this help"},
    {0, none, 		"unknown command, try help"}
} ;

/* ------------------------------
   dialog and execute
   ------------------------------------------------------------*/

static void
execute(const char *name)
{
    struct _cmd *c = commands;

    while (c->name && strcmp (name, c->name))
	c++;
    (*c->fun)(c);
}

static void
loop(void)
{
    char name[64];

    while (printf("> "), scanf("%62s", name) == 1)
	execute(name) ;
}

/* ------------------------------
   command execution
   ------------------------------------------------------------*/
static void
list(struct _cmd *c)
{
    printf("%s NYI\n", c->name);
}

static void
new(struct _cmd *c) {
  struct volume_s vol;

  read_mbr();

  scanf("Taille (en secteurs): %u\n", &vol.vol_nSector);
  scanf("Indice cylindre: %u\n", &vol.vol_first_cylinder);
  scanf("Indice secteur: %u\n", &vol.vol_first_sector);

  vol.vol_type = VOL_BASIC;
  mbr.mbr_vols[mbr.mbr_nVol++] = vol;

  write_mbr();
}

static void
del(struct _cmd *c)
{
    printf("%s NYI\n", c->name);
}

static void
save(struct _cmd *c)
{
    printf("%s NYI\n", c->name);
}

static void
quit(struct _cmd *c)
{
    printf("%s NYI\n", c->name);
    exit(EXIT_SUCCESS);
}

static void
do_xit()
{
    exit(EXIT_SUCCESS);
}

static void
xit(struct _cmd *dummy)
{
    do_xit();
}

static void
help(struct _cmd *dummy)
{
    struct _cmd *c = commands;

    for (; c->name; c++)
	printf ("%s\t-- %s\n", c->name, c->comment);
}

static void
none(struct _cmd *c)
{
    printf ("%s\n", c->comment) ;
}

static void empty_it() {
  return;
}

int
main(int argc, char **argv)
{
  int i;
  if(init_hardware("hardware.ini") == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }

  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);

  /* dialog with user */
  loop();

  /* abnormal end of dialog (cause EOF for xample) */
  do_xit();

  /* make gcc -W happy */
  exit(EXIT_SUCCESS);
}
