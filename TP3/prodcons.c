#include "sem.h"
#define N 2

typedef int objet_t;
struct sem_s mutex, vide, plein;

static int cpt = 0;
static objet_t buffer[N];

void produire_objet (objet_t * objet) {
  cpt++;
  *objet = cpt;
  printf("Produit l'objet %d\n", *objet);
}

void mettre_objet (objet_t objet) {
  int i = 0;
  while (buffer[i] != -1)
    i++;
  buffer[i] = objet;
  printf("Met l'objet %d à l'indice %d\n", objet, i);
}

void retirer_objet (objet_t * objet) {
  int i = 0;
  while (buffer[i] == -1 && i < N)
    i++;
  *objet = buffer[i];
  buffer[i] = -1;
  printf("Retire l'objet %d à l'indice %d\n", *objet, i);
}

void utiliser_objet (objet_t objet) {
  cpt--;
  printf("Utilise l'objet %d\n", objet);
}

void producteur () {
  objet_t objet;

  while (1) {
    produire_objet(&objet);
    sem_down(&vide);
    sem_down(&mutex);
    mettre_objet(objet);
    sem_up(&mutex);
    sem_up(&plein);
  }
}

void consommateur () {
  objet_t objet;

  while (1) {
    sem_down(&plein);
    sem_down(&mutex);
    retirer_objet(&objet);
    sem_up(&mutex);
    sem_up(&vide);
    utiliser_objet(objet);
  }
}

int main (int argc, char * argv[]) {
  sem_init(&mutex, 1);
  sem_init(&vide, N);
  sem_init(&plein, 0);

  for (int i = 0; i < N; i++)
    buffer[i] = -1;

  create_ctx(16384, producteur, NULL);
  create_ctx(16384, consommateur, NULL);

  start_schedule();

  printf("hello world\n");
  exit(EXIT_SUCCESS);
}
