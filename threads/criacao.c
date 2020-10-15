#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *PrintHello(void *threadid) //se eu quisesse passar mais argumentos --> struct
{
  printf("Ola, mundo!\n");
  pthread_exit(NULL); //eh o que eu retorno quando a thread acaba
}
int main(int argc, char *argv[])
{
  //quando eu entro aqui já existe uma thread em execução (a main)
  pthread_t thread; //declarar thread
  int rc;
  rc = pthread_create(&thread, NULL, PrintHello, NULL); // (variável que contém a thread, atributos → se não quiser mexer em nada, manda NULL, código da thread, argumento da função)
  if (rc) //se retornou algo != de NULL, é pq deu erro
  {
    printf("ERRO; codigo de retorno eh %d\n", rc);
    exit(-1);
  }
  printf("Main\n");
  pthread_exit(NULL); //isso aqui PRECISA existir, se não tiver, a main não vai esperar todas as threads terminarem e elas vão deixar de existir
}
// pra compilar:
// gcc -lpthread arquivo.c -o a
// ou
// gcc -pthread arquivo.c -o a --> esse que funciona aqui