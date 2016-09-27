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
    switch_to_ctx(&ctx_pong);
    printf("B");
    switch_to_ctx(&ctx_pong);
    printf("C");
    switch_to_ctx(&ctx_pong);
  }
}

void f_pong (void * args) {
  while (1) {
    printf("1");
    switch_to_ctx(&ctx_ping);
    printf("2");
    switch_to_ctx(&ctx_ping);
  }
}

void f_ping_ended (void * args) {
  while (1) {
    printf("A");
    switch_to_ctx(&ctx_pong_ended);
    printf("B");
    switch_to_ctx(&ctx_pong_ended);
    printf("C");
    switch_to_ctx(&ctx_pong_ended);
  }
}

void f_pong_ended (void * args) {
  printf("1");
  switch_to_ctx(&ctx_ping_ended);
  printf("2");
  switch_to_ctx(&ctx_ping_ended);
}

int main() {
  init_ctx(&ctx_ping_ended, 16384, f_ping_ended, NULL);
  init_ctx(&ctx_pong_ended, 16384, f_pong_ended, NULL);
  switch_to_ctx(&ctx_ping_ended);

  /*init_ctx(&ctx_ping, 16384, f_ping, NULL);
  init_ctx(&ctx_pong, 16384, f_pong, NULL);
  switch_to_ctx(&ctx_ping);*/

  printf("hello world\n");
  exit(EXIT_SUCCESS);
}
