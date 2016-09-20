int main () {
  long int esp, ebp;

  asm("movl %%esp, %0"
        : "=r" (esp));
  asm("movl %%ebp, %0"
        : "=r" (ebp));

  printf("esp : %#010x\t ebp : %#010x\n", esp, ebp);
}
