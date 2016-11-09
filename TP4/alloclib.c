#include <time.h>
#include "current.c"

extern struct super_s super;

static void empty_it() {
  return;
}

int main(int argc, char const *argv[]) {
  int i, r, tmp;
  if(init_hardware(get_hw_config()) == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }

  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);

  read_mbr();

  load_current_volume();

  tmp = super.super_nFree;

  while (new_bloc()) {
    printf("Alloue un bloc\n");
  }

  if(super.super_nFree == 0)
    printf("Le volume est plein\n");

  srand(time(NULL));
  r = rand() % tmp;

  for(i = 0; i < r; i++) {
    free_bloc(i + 1);
  }

  printf("%u blocs libere\n", super.super_nFree);

  tmp = 0;
  while (new_bloc()) {
    tmp++;
  }

  printf("%d bloc qui ont pu etre aloue\n", tmp);

  return 0;
}
