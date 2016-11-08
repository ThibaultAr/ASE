#include "current.c"

static void empty_it() {
  return;
}

int main(int argc, char const *argv[]) {
  int i;
  if(init_hardware(get_hw_config()) == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }

  for(i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);

  read_mbr();

  init_super(load_current_volume());

  return 0;
}
