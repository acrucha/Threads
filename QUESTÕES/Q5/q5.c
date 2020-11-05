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

// int b[linhas] = {40, 45, 21, 32};
int b[linhas] = {40, 45, 21, 32};
int x[linhas] = {};

pthread_mutex_t barrier = PTHREAD_MUTEX_INITIALIZER; //estático
pthread_cond_t ir = PTHREAD_COND_INITIALIZER;   //condicional

void Barreira();
void *thread_function(void *argumento);

int main(){
    int i, j;
    printf("Quantidade de threads = ");
    scanf("%d", &qtd_threads);
    int id[qtd_threads]; 
    for (int a = 0; a < qtd_threads; a++){
        id[a] = a;
    }
    int t;
    int status;
    pthread_t thread[qtd_threads];
    for (t = 0; t < qtd_threads; t++){
        status = pthread_create(&thread[t], NULL, thread_function, (void *)&id[t]);
        if (status){
            printf("ERRO; codigo de retorno eh %d\n", status);
            exit(-1);
        }
    }
    for (i = 0; i < qtd_threads; i++) 
    {
        pthread_join(thread[i], NULL);
    }
    for(i=0; i<linhas; i++){
        printf("x[%d] = %d\n", i, x[i]);
    }

    return 0;
}

void *thread_function(void *argumento){
    int k=0, soma=0, i, j;
    int id = *(int*)argumento;
    int X[linhas];
    for(i=0;i<linhas;i++){
        X[i] = 1; // criando os anteriores
    }
    //puts("oi");
    while (k < P){
        for (i=id; i<linhas; i+=qtd_threads){
            soma = 0;
            for (j=0; j<linhas; j++){
                if(j!=i){ 
                    //puts("entrei");
                    soma = soma + A[i][j]*X[j]; // X é o vetor de k
                }
            }
            //printf("soma = %d\n", soma);
            x[i] = (b[i] - soma)/A[i][i]; // x é o vetor de k + 1
        }   
        for(j = 0; j < linhas; j++){
            X[j] = x[j];    // fazendo uma cópia de x de k
        }
        Barreira();
        k = k + 1;
    }
    //pthread_exit(NULL);
}

void Barreira() {
  pthread_mutex_lock(&barrier);
  threadsAtuais++;
  if (threadsAtuais == qtd_threads) {
     // puts("hello");
    threadsAtuais = 0;
    pthread_cond_broadcast(&ir);
  } else
    pthread_cond_wait(&ir, &barrier);
  pthread_mutex_unlock(&barrier);
}