#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *PrintHello(void *threadid) //é void * pq é o que a criação de threads exige
{
  int tid = *((int *)threadid);
  printf("Ola, mundo! Sou eu, a thread #%d!\n", tid);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS]; //eu crio um array com a quantidade de threads que eu quero
  int *taskids[NUM_THREADS]; //crio um array pra ser minhas threads filhas --> tem que ser ponteiro senão da merda

  int rc;
  int t;
  for (t = 0; t < NUM_THREADS; t++) //rodo o array
  {
    taskids[t] = (int *)malloc(sizeof(int)); //pra cada posição, eu aloco
    *taskids[t] = t; //e digo q o valor é igual a esse número
    printf("Na main: criando thread %d\n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *)taskids[t]); //aqui o argumento da função é justamente aquele valr q eu dei
    if (rc)
    {
      printf("ERRO; codigo de retorno eh %d\n", rc);
      exit(-1);
    }
  }
  pthread_exit(NULL);
  for (int i = 0; i < 5; i++)
  {
    free (taskids[i]);
  }
}
