#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define P 15
#define linhas 4
int qtd_threads, threadsAtuais = 0;

double A[linhas][linhas] = {
    9, 1, 3, 3,
    3, 8, 2, 1, 
    3, 1, 6, 1, 
    3, 1, 3, 8
};

int b[linhas] = {23, 12, 15, 84};
//x1 ~= -1,4466, x2 ~= 0,3805, x3 ~= 1,4159 , x4 ~= 10,4639

double x[linhas] = {};

pthread_mutex_t barrier = PTHREAD_MUTEX_INITIALIZER; //estático
pthread_cond_t ir = PTHREAD_COND_INITIALIZER;   //condicional

void Barreira();
void *thread_function(void *argumento);

int main(){
    int i, j;
    printf("Quantidade de threads = ");
    scanf("%d", &qtd_threads);
    int id[qtd_threads]; 
    for (int a = 0; a < qtd_threads; a++){//cria os ids das threads 
        id[a] = a;
    }
    int t;
    int status;
    pthread_t thread[qtd_threads];
    for (t = 0; t < qtd_threads; t++){//cria as threads
        status = pthread_create(&thread[t], NULL, thread_function, (void *)&id[t]);
        if (status){
            printf("ERRO; codigo de retorno eh %d\n", status);
            exit(-1);
        }
    }
    for (i = 0; i < qtd_threads; i++) //como a barreira esta antes da atribuição do K++ não ocorre o bloqueio na ultima atribuição sendo assim necessario o join na main.
    {
        pthread_join(thread[i], NULL);
    }
    for(i=0; i<linhas; i++){//printa a resposta
        printf("x[%d] = %.4lf\n", i, x[i]);
    }
    return 0;
}

void *thread_function(void *argumento){
    int k = 0, i, j;
    double soma = 0;

    int id = *(int*)argumento;//tranforma para inteiro
    double X[linhas]; // criando um vetor auxiliar para guardar o antecessor de x
    
    for(i=0;i<linhas;i++){
        X[i] = 1; // atribuindo os valores iniciais para 1
    }
    
    while (k < P){ //enquanto k for menor que o número de interações 
        for (i=id; i<linhas; i+=qtd_threads){ // cada thread vai modificar o seu xi de posição i+qtd_threads partindo do seu id     
            soma = 0;                         // ou seja, a thread[id] vai pegar inicialmente xi[id] e depois continuará de qtd_threads em qtd_threads
            for (j=0; j<linhas; j++){
                if(j!=i){ 
                    soma = soma + A[i][j]*X[j]; // X é o vetor de k
                }
            }
            x[i] = (b[i] - soma)/A[i][i]; // x é o vetor de k + 1
        }   
        for(j = 0; j < linhas; j++){
            X[j] = x[j];    // fazendo uma cópia de x de k
        }
        Barreira();//chama a função de barreira
        k = k + 1;
    }
    pthread_exit(NULL);
}

void Barreira() {// recebe a thread em execução na função e faz verificações
  pthread_mutex_lock(&barrier);
  threadsAtuais++;//verifica a qtd de threads
  if (threadsAtuais == qtd_threads) {//verifica se todas as threads chegaram
    threadsAtuais = 0;
    pthread_cond_broadcast(&ir);//libera as threads da barreira apos a chegada da ultima
  } else
    pthread_cond_wait(&ir, &barrier);//faz a thread dormir
  pthread_mutex_unlock(&barrier);
}