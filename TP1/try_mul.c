#include "try.h"
#include <stdio.h>

struct ctx_s env;

int mul (int depth) {
  int i;
  switch (scanf ("%d", &i)) {
    case EOF:
      return 1;
    case 0:
      return mul (depth + 1);
    case 1:
      if (i)
        return i * mul (depth + 1);
      else
        throw(&env, 0);
  }
}

int main () {
  int product;

  printf ("A list of int, please\n");
  product = try(&env, mul, 0);
  printf("product = %d\n", product);

  return 0;
}
