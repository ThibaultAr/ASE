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
  printf("func: nothing_to_do ");
  display_stack(esp, ebp);
}

int useless_cpt(int n) {
  long int esp, ebp;

  asm("movl %%esp, %0"
        : "=r" (esp));
  asm("movl %%ebp, %0"
        : "=r" (ebp));
  printf("func: useless_cpt ");
  display_stack(esp, ebp);
  printf("param : %#010x\n", &n);

  if(n == 0)
    return n;
  else
    1 + useless_cpt(n - 1);
}

int main () {
  long int esp, ebp;

  asm("movl %%esp, %0"
        : "=r" (esp));
  asm("movl %%ebp, %0"
        : "=r" (ebp));

  display_stack(esp, ebp);
  nothing_to_do();
  useless_cpt(3);

}
