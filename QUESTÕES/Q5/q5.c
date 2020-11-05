#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define P 10
#define linhas 4
int qtd_threads, threadsAtuais = 0;

int A[linhas][linhas] = {
    9, 1, 3, 3,
    3, 8, 2, 1, 
    3, 1, 6, 1, 
    3, 1, 3, 8
};
//x1 = 3, x2 = 4, x3 = 1, x4 = 2

int b[linhas] = {40, 45, 21, 32};
int x[linhas][P];

pthread_mutex_t barrier = PTHREAD_MUTEX_INITIALIZER; //estático
pthread_cond_t ir = PTHREAD_COND_INITIALIZER;   //condicional

void Barreira();
void *thread_function(void *argumento);

int main(){
    int i, j;
    printf("Quantidade de threads = ");
    scanf("%d\n", &qtd_threads);
    int x[qtd_threads]; 
    for (int a = 0; a < qtd_threads; a++){
        x[a] = a;
    }
    int t;
    int status;
    pthread_t thread[qtd_threads];
    for (t = 0; t < qtd_threads; t++){
        status = pthread_create(&thread[t], NULL, thread_function, (void *)&x[t]);
        if (status){
            printf("ERRO; codigo de retorno eh %d\n", status);
            exit(-1);
        }
    }
    for(i=0; i<P; i++){
        printf("Interacao %d\n\n", i+1);
        for(j=0; j<linhas; j++){
            printf("x[%d] = %d\n", i, x[j][i]);
        }
    }
    return 0;
}

void *thread_function(void *argumento){
    int k=0, soma=0, i, j;
    int id = *(int*)argumento;
    for(i=0;i<P;i++){
        x[i][0] = 1;
    }
    while (k < P){
        for (i=id; i<linhas; i+=qtd_threads){
            soma = 0;
            for (j=0; j<linhas; j++){
                if(j!=i){
                    soma = soma + A[i][j]*x[j][k];
                }
            }
            x[i][k+1] = (b[i] - soma)/A[i][i];
        }   
        Barreira();
        k = k + 1;
    }
}

void Barreira() {
  pthread_mutex_lock(&barrier);
  threadsAtuais++;
  if (threadsAtuais == qtd_threads) {
    threadsAtuais = 0;
    pthread_cond_broadcast(&ir);
  } else
    pthread_cond_wait(&ir, &barrier);
  pthread_mutex_unlock(&barrier);
}