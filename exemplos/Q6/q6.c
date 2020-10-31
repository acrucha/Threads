#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define B 8           //tamanho do buffer
#define C 2           //quantidade de threads consumidoras
#define P 3           //quantidade de threads produtoras
#define NUM_BUFFERS 1 //quantidade de buffers
#define NUM_ITEMS 100

typedef struct elem
{
  int value;
  struct elem *prox;
} Elem;

typedef struct blockingQueue
{
  unsigned int sizeBuffer, statusBuffer;
  Elem *head, *last;
} BlockingQueue;

BlockingQueue *newBlockingQueue(unsigned int SizeBuffer); //cria uma nova fila
void putBlockingQueue(BlockingQueue *Q, int newValue);    // insere um novo elemento no final da fila
int takeBlockingQueue(BlockingQueue *Q);                  //retira primeiro elemento da fila bloaqueante, ela dorme se tiver vazia
int pegar(BlockingQueue *Q);
void colocar(BlockingQueue *Q);
void *retirar(void *Q);
void *inserir(void *Q);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //estático
pthread_cond_t vazio = PTHREAD_COND_INITIALIZER;   //condicional (se estiver vazio)
pthread_cond_t cheio = PTHREAD_COND_INITIALIZER;   //condicional (se estiver cheio)

int main()
{
  pthread_t consumidoras[C]; // criacao três threads consumidoras
  pthread_t produtoras[P];   //criacao uma thread produtora
  int i, j, rc;

  BlockingQueue *Q = newBlockingQueue(B); //vai criar uma Q do tamanho B e vai dar errado do jeito q ta aqui se NUM_BUFFERS for > 1
  for (j = 0; j < NUM_BUFFERS; j++)       //roda pra cada um dos buffers
  {
    for (i = 0; i < P; i++)
    {
      rc = pthread_create(&produtoras[i], NULL, inserir, (void *)&Q[j]);
      if (rc)
      {
        printf("ERRO!");
        exit(-1);
      }
    }
    /*for (i = 0; i < C; i++)
    {
      rc = pthread_create(&consumidoras[i], NULL, retirar, (void *)&Q[j]);
      if (rc)
      {
        printf("ERRO!");
        exit(-1);
      }
    }*/
  }
  for (i = 0; i < P; i++) //fazer a main esperar pela conclusão das produtoras e consumidoras:
  {
    pthread_join(produtoras[i], NULL);
  }
  // for (i = 0; i < C; i++)
  // {
  //   pthread_join(consumidoras[i], NULL);
  // }
  return 0;
}

BlockingQueue *newBlockingQueue(unsigned int SizeBuffer) // vai dar errado do jeito q ta aqui se NUM_BUFFERS for > 1
{                                                                           //acho q ta certo ja isso
  BlockingQueue *fila = (BlockingQueue *)malloc(sizeof(BlockingQueue) * NUM_BUFFERS); //eu aloco 1 unidade de fila
  fila->head = NULL;                                                        //primeiro da fila bloqueante
  fila->last = NULL;                                                        //ultimo da fila bloqueante
  fila->sizeBuffer = SizeBuffer;
  fila->statusBuffer = 0; //o buffer vazio inicialmente
  return fila;
}

void *inserir(void *Q) //inserir elemento no buffer e pode ser que de errado do jeito q ta aqui se NUM_BUFFERS for > 1
{
  BlockingQueue *lista = (BlockingQueue*)Q; 
  //printf("%d\n",lista->sizeBuffer);
  int i;
  for (i = 0; i < NUM_ITEMS * 3; i++) {
    colocar(lista);
    printf ("Produzi : %d\n", i);
  }
  pthread_exit(NULL);
}

void colocar(BlockingQueue *Q) //vai dar errado do jeito q ta aqui se NUM_BUFFERS for > 1
{
  pthread_mutex_lock(&mutex);    //bloqueio: ninguém pode usar
  while ((Q->statusBuffer) == B) //se tiver cheio, não posso encher
  {                              //dentro de um while pra rechecar, pra evitar que acorde sem ser verdade
    printf("A fila esta cheia!!! Vou de berço...(u.u)\n");
    pthread_cond_wait(&vazio, &mutex); //aguardo a condição de estar vazio
  }
  int newValue = Q->statusBuffer;
  putBlockingQueue(Q, newValue);
  printf("oi\n");
  if ((Q->statusBuffer) == 1) //se não estiver mais vazio, mando acordar todos consumidores dizendo que eles podem agir
  {
    pthread_cond_broadcast(&cheio); // acordo todas as outras threads que não esta mais vazia
  }
  pthread_mutex_unlock(&mutex); //desbloqueio pra os consumidores poderem usar
}

void putBlockingQueue(BlockingQueue *Q, int newValue) //vai dar errado do jeito q ta aqui se NUM_BUFFERS for > 1
{
  Elem *newElem = (Elem *)malloc(sizeof(Elem)*1); //criei elemento
  Elem *aux = Q->last;
  newElem->value = newValue;
  newElem->prox = aux->prox;
  Q->last = newElem;
  printf("newValue = %d\n", newElem->value);
  (Q->statusBuffer)++; // incrementando tamanho atual do buffer
}

void *retirar(void *Q) //vai dar errado do jeito q ta aqui se NUM_BUFFERS for > 1
{
  //transforma de void pra estrutura
  int i, v;
  printf("Consumidor\n");
  for (i = 0; i < NUM_ITEMS*2; i++)
  {
    v = pegar(Q);
    printf("\nConsumi %d  \n", v);
  }
  pthread_exit(NULL);
}
   
int pegar(BlockingQueue *Q) //vai dar errado do jeito q ta aqui se NUM_BUFFERS for > 1 (SENDO que, Tem um for la fora, entao devia funcionar nao?)
{
  int valor;
  pthread_mutex_lock(&mutex); //bloqueio pra só um ter acesso
  while ((Q->statusBuffer) == 0) //se tiver vazio, durmo até um produtor me acordar
  {
    printf("A fila esta vazia!!! Vou de berço...(u.u)\n");
    pthread_cond_wait(&cheio, &mutex);
  }
  valor = takeBlockingQueue(Q); //recebendo o valor do elemento retirado
  if ((Q->statusBuffer) == (Q->sizeBuffer) - 1)
  {
    pthread_cond_signal(&vazio);
  }
  pthread_mutex_unlock(&mutex);
  return valor;
}

int takeBlockingQueue(BlockingQueue *Q) //vai dar errado do jeito q ta aqui se NUM_BUFFERS for > 1
{
  Elem *prox = Q->head;
  int value = prox->value;
  Q->head = prox->prox;
  (Q->statusBuffer)--; // decrementando tamanho atual do buffer
  free(prox);
  
  return value;
}