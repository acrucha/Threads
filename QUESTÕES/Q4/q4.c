#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define B 10  //máximo do buffer
#define N 5 //numero de threads
typedef struct{
    int p1, p2;
} Parametros;

typedef struct{
    int funcao;
    int id;
    Parametros parametro;
}agendamento;

agendamento buffer[B]; //guarda os agendamentos
agendamento resposta[B]; //guarda as respostas de cada agendamento
int statusBuffer = 0; //diz quantos agendamentos ha no buffer atualmente

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //estático
pthread_cond_t vazio = PTHREAD_COND_INITIALIZER;   //condicional (se estiver vazio)
pthread_cond_t cheio = PTHREAD_COND_INITIALIZER;  

void *despachante();
void criarThreads();

void *multiplicar(void *q);
void *somar(void *q);
void *subtrair(void *q);

int main(){
    int rc;
    //agendar todas requisicoes do usuario  e retornar o id
    //quando receber -1:
    //criar a thread despachante
    pthread_t threadDespachante; //responsavel por gerenciar as N threads
    rc = pthread_create(&threadDespachante, NULL, despachante, NULL);
    if (rc)
    {
      printf("ERRO!");
      exit(-1);
    }
    
    return 0;
}


void *despachante(){
    pthread_mutex_lock(&mutex);    //bloqueio pra só um ter acesso
    while (statusBuffer == 0) //se tiver vazio, durmo até um produtor me acordar
    {
        printf("A fila esta vazia!!!\n");
        pthread_cond_wait(&cheio, &mutex);
    }
    criarThreads();                
    if (statusBuffer == B - 1) //se nao esta mais cheio, acordar produtores
    {
        pthread_cond_signal(&vazio);
    }
    pthread_mutex_unlock(&mutex);
}

void *multiplicar(void *q){
    Parametros p = (*(Parametros *) q);
    int resultado = p.p1 * p.p2;
}
void *somar(void *q){
    Parametros p = (*(Parametros *) q);
    int resultado = p.p1 + p.p2;
}
void *subtrair(void *q){
    Parametros p = (*(Parametros *) q);
    int resultado = p.p1 - p.p2;
}

void criarThreads()
{
    int rc, i;
    pthread_t threads[N];
    //100
    for(i=0;i<B;i++){
        if(buffer[i].funcao == 0){
            rc = pthread_create(&threads[i], NULL, multiplicar, (void *)&buffer[i].parametro);
            if (rc)
            {
                printf("ERRO!");
                exit(-1);
            }
        }
        else if(buffer[i].funcao == 1){
            rc = pthread_create(&threads[i], NULL, somar, (void *)&buffer[i].parametro);
            if (rc)
            {
                printf("ERRO!");
                exit(-1);
            }
        }
        else if(buffer[i].funcao == 2){
            rc = pthread_create(&threads[i], NULL, subtrair, (void *)&buffer[i].parametro);
            if (rc)
            {
                printf("ERRO!");
                exit(-1);
            }
        }
    }
    
}
