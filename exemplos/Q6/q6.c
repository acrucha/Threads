#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define B 8
#define C 2
#define P 3

typedef struct elem{
   int value;
   struct elem *prox;
}Elem;
 
typedef struct blockingQueue{
   unsigned int sizeBuffer, statusBuffer;
   Elem *head,*last;
}BlockingQueue;

 
BlockingQueue *newBlockingQueue(unsigned int SizeBuffer);//cria uma nova fila

void putBlockingQueue(BlockingQueue* Q, int newValue);// insere um novo elemento no final da fila

int takeBlockingQueue(BlockingQueue* Q); //retira primeiro elemento da fila bloaqueante, ela dorme se tiver vazia

// haverá threads consumidoras e threads produtoras
//sem espera ocupada

int main()
{

    return 0;
}