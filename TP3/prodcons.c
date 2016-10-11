#include "sem.h"
#define N 2

typedef int objet_t;
struct sem_s mutex, vide, plein;

static int cpt = 0;
static objet_t buffer[N];

void produire_objet (objet_t * objet, int num) {
  cpt++;
  *objet = cpt;
  printf("P%d Produit l'objet %d\n", num, *objet);
}

void mettre_objet (objet_t objet, int num) {
  int i = 0;
  while (buffer[i] != -1)
    i++;
  buffer[i] = objet;
  printf("P%d Met l'objet %d à l'indice %d\n", num, objet, i);
}

void retirer_objet (objet_t * objet, int num) {
  int i = 0;
  while (buffer[i] == -1 && i < N)
    i++;
  *objet = buffer[i];
  buffer[i] = -1;
  printf("C%d Retire l'objet %d à l'indice %d\n", num, *objet, i);
}

void utiliser_objet (objet_t objet, int num) {
  cpt--;
  printf("C%d Utilise l'objet %d\n", num, objet);
}

void producteur (void* num) {
  objet_t objet;

  while (1) {
    produire_objet(&objet, (int)num);
    sem_down(&vide);
    sem_down(&mutex);
    mettre_objet(objet, (int)num);
    sem_up(&mutex);
    sem_up(&plein);
  }
}

void consommateur (void* num) {
  objet_t objet;

  while (1) {
    sem_down(&plein);
    sem_down(&mutex);
    retirer_objet(&objet, (int)num);
    sem_up(&mutex);
    sem_up(&vide);
    utiliser_objet(objet, (int)num);
  }
}

int main (int argc, char * argv[]) {
  sem_init(&mutex, 1);
  sem_init(&vide, N);
  sem_init(&plein, 0);

  for (int i = 0; i < N; i++)
    buffer[i] = -1;

  create_ctx(16384, producteur, (void*)1);
  create_ctx(16384, consommateur, (void*)1);
  create_ctx(16384, consommateur, (void*)2);
  create_ctx(16384, consommateur, (void*)3);

  start_schedule();

  printf("hello world\n");
  exit(EXIT_SUCCESS);
}
