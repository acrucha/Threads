#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define B 8 //tamanho do buffer
#define C 4 //quantidade de threads consumidoras
#define P 1 //quantidade de threads produtoras

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
int takeBlockingQueue(BlockingQueue *Q);                  //retira primeiro elemento da fila bloqueante
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

  BlockingQueue *Q = newBlockingQueue(B); //vai criar uma Q do tamanho B
  for (i = 0; i < P; i++)
  {
    rc = pthread_create(&produtoras[i], NULL, inserir, (void *)Q);
    if (rc)
    {
      printf("ERRO!");
      exit(-1);
    }
  }
  for (i = 0; i < C; i++)
  {
    rc = pthread_create(&consumidoras[i], NULL, retirar, (void *)Q);
    if (rc)
    {
      printf("ERRO!");
      exit(-1);
    }
  }
  //fazer a main esperar pela conclusão das produtoras e consumidoras:
  for (i = 0; i < P; i++) 
  {
    pthread_join(produtoras[i], NULL);
  }
  for (i = 0; i < C; i++)
  {
    pthread_join(consumidoras[i], NULL);
  }
  return 0;
}

BlockingQueue *newBlockingQueue(unsigned int SizeBuffer)
{
  BlockingQueue *fila = (BlockingQueue *)malloc(sizeof(BlockingQueue) * 1);
  fila->last = NULL;
  fila->head = fila->last;
  fila->sizeBuffer = SizeBuffer;
  fila->statusBuffer = 0; //o buffer vazio inicialmente
  return fila;
}

void *inserir(void *Q) //funcao da thread produtora
{
  BlockingQueue *lista = (BlockingQueue *)Q;
  printf("%d\n", lista->sizeBuffer);
  int i;
  while (1)
  {
    colocar(lista);
    printf("Produzi : %d\n", i);
  }
  pthread_exit(NULL);
}

void colocar(BlockingQueue *Q)
{
  pthread_mutex_lock(&mutex);    //bloqueio: ninguém pode usar o buffer
  while ((Q->statusBuffer) == B) //se tiver cheio, não posso encher
  {                              //dentro de um while pra rechecar
    printf("A fila esta cheia!!!s\n");
    pthread_cond_wait(&vazio, &mutex); //aguardo a condição ser atendida
  }
  int newValue = Q->statusBuffer;
  putBlockingQueue(Q, newValue);
  if ((Q->statusBuffer) == 1) //se não estiver mais vazio, mando acordar todos consumidores dizendo que eles podem agir
  {
    pthread_cond_broadcast(&cheio); // acordo todas as outras threads, indicando que não esta mais vazio
  }
  pthread_mutex_unlock(&mutex); //desbloqueio pra os consumidores poderem usar
}

void putBlockingQueue(BlockingQueue *Q, int newValue)
{
  Elem *newElem = (Elem *)malloc(sizeof(Elem) * 1);
  Elem *cur = Q->head;
  if (cur != NULL)
  {
    while (cur->prox != NULL)
    {
      cur = cur->prox;
    }
    newElem->value = newValue;
    newElem->prox = NULL;
    cur->prox = newElem;
    Q->last = newElem;
  }
  else
  {
    Q->head = newElem;
    newElem->value = newValue;
    newElem->prox = NULL;
    Q->last = newElem;
  }
  (Q->statusBuffer)++;
}

void *retirar(void *Q)
{
  int i, v;
  printf("Consumidor\n");
  while (1)
  {
    v = pegar(Q);
    printf("\nConsumi %d  \n", v);
  }
  pthread_exit(NULL);
}

int pegar(BlockingQueue *Q)
{
  int valor;
  pthread_mutex_lock(&mutex);    //bloqueio pra só um ter acesso
  while ((Q->statusBuffer) == 0) //se tiver vazio, durmo até um produtor me acordar
  {
    printf("A fila esta vazia!!!s\n");
    pthread_cond_wait(&cheio, &mutex);
  }
  valor = takeBlockingQueue(Q);                 //recebendo o valor do elemento retirado
  if ((Q->statusBuffer) == (Q->sizeBuffer) - 1) //se nao esta mais cheio acordar produtores agora
  {
    pthread_cond_signal(&vazio);
  }
  pthread_mutex_unlock(&mutex);
  return valor;
}

int takeBlockingQueue(BlockingQueue *Q)
{
  Elem *prox = (Elem *)malloc(sizeof(Elem) * 1);
  prox = Q->head;
  int value = prox->value;
  Q->head = prox->prox;
  (Q->statusBuffer)--;
  free(prox);

  return value;
}