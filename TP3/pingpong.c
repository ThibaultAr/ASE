#include "ctx.h"
#include <stdio.h>
#include <stdlib.h>

struct ctx_s ctx_ping;
struct ctx_s ctx_pong;
struct ctx_s ctx_ping_ended;
struct ctx_s ctx_pong_ended;

void f_ping (void * args) {
  while (1) {
    printf("A");
    yield();
    printf("B");
    yield();
    printf("C");
    yield();
  }
}

void f_pong (void * args) {
  while (1) {
    printf("1");
    yield();
    printf("2");
    yield();
  }
}

void f_ping_ended (void * args) {
    printf("A");
    yield();
    printf("B");
    yield();
    printf("C");
    yield();
}

void f_pong_ended (void * args) {
  printf("1");
  yield();
  printf("2");
  yield();
}

int main() {
  /*create_ctx(16384, f_ping, NULL);
  create_ctx(16384, f_pong_ended, NULL);*/

  /*create_ctx(16384, f_ping, NULL);
  create_ctx(16384, f_pong, NULL);*/

  create_ctx(16384, f_ping_ended, NULL);
  create_ctx(16384, f_pong_ended, NULL);

  yield();

  printf("hello world\n");
  exit(EXIT_SUCCESS);
}
