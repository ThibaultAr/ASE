#include <stdio.h>

void display_stack(long int esp, long int ebp) {
  printf("esp : %#010x\t ebp : %#010x\n", esp, ebp);
}

void nothing_to_do() {
  long int esp, ebp;

  asm("movl %%esp, %0"
        : "=r" (esp));
  asm("movl %%ebp, %0"
        : "=r" (ebp));

  display_stack(esp, ebp);
}

int main () {
  long int esp, ebp;

  asm("movl %%esp, %0"
        : "=r" (esp));
  asm("movl %%ebp, %0"
        : "=r" (ebp));

  display_stack(esp, ebp);

  asm("movl %%esp, %0"
        : "=r" (esp));
  asm("movl %%ebp, %0"
        : "=r" (ebp));

  nothing_to_do();
}
