#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 200

int buff[BUFFER_SIZE]; /* buffer size = 10; */
int items = 0;         // number of items in the buffer.
int first = 0;
int last = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //estático
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;   //estatico
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;    //estatico

void *producer();
void *consumer();

int main()
{
    pthread_t consumer_thread[3]; //três threads consumidoras
    pthread_t producer_thread;    //uma thread produtora
    int i;
    for (i = 0; i < 3; i++)
        pthread_create(&consumer_thread[i], NULL, consumer, NULL);
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_join(producer_thread, NULL);
    for (i = 0; i < 3; i++)
        pthread_join(consumer_thread[i], NULL);
}

void put(int i)
{
    pthread_mutex_lock(&mutex);            //bloqueio: ninguém pode usar
    while (items == BUFFER_SIZE)           //se tiver cheio, não posso encher
    {                                      //dentro de um while pra rechecar, pra evitar que acorde sem ser verdade
        pthread_cond_wait(&empty, &mutex); //aguardo a condição de estar vazio
        //OBS: é um while, mas não é uma espera ocupada, ele só dorme enquanto espera alguém acordar ele
    }
    buff[last] = i; //coloco i na ultima posicao do buffer
    printf("\npos %d: ", last);
    items++; //aumento a qtd de itens
    printf("\nqtd de itens: %d", items);
    last++;
    if (last == BUFFER_SIZE) //se eu cheguei no tamanho máximo do buffer
    {
        last = 0; //eu volto pro começo? por que?
    }
    if (items == 1) //se não estiver mais vazio, mando acordar todos consumidores dizendo que eles podem agir
    {
        pthread_cond_broadcast(&fill); // acordo todas as outras threads
    }
    pthread_mutex_unlock(&mutex); //desbloqueio pra os consumidores poderem usar
}

void *producer()
{
    int i = 0;
    printf("Produtor\n");
    for (i = 0; i < NUM_ITEMS * 3; i++)
    {
        put(i);
        printf("Produzi %d \n", i);
    }
    pthread_exit(NULL);
}

int get()
{
    int result;
    pthread_mutex_lock(&mutex); //bloqueio pra só um ter acesso
    while (items == 0)          //se tiver vazio, durmo até um produtor me acordar
    {
        pthread_cond_wait(&fill, &mutex);
    }
    result = buff[first];
    printf("pos %d: ", first);
    items--;
    first++;
    if (first == BUFFER_SIZE)
    {
        first = 0;
    }
    if (items == BUFFER_SIZE - 1)
    {
        pthread_cond_signal(&empty);
    }
    pthread_mutex_unlock(&mutex);
    return result;
}
void *consumer()
{
    int i, v;
    printf("Consumidor\n");
    for (i = 0; i < NUM_ITEMS; i++)
    {
        v = get();
        printf("\nConsumi %d  \n", v);
    }
    pthread_exit(NULL);
}
