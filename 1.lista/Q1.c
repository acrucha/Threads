#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long contador = 0;
int flag = 0; //determina se o contador chegou ou não a 1000000
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //mutex estático

void *inc(void *threadid) //funcao de incrementar, recebe id da thread como parâmetro
{
    while (flag == 0)
    {
        pthread_mutex_lock(&mutex); //impede que outras threads utilizem o contador ao mesmo tempo
        if (contador < 1000000)
        {
            contador++;
            if (contador == 1000000)
            {
                int tid = *((int *)threadid);
                printf("o valor é %ld \n", contador);
                printf("a thread é %d \n", tid);
                flag = 1; //determina que o contador chegou a 1000000, impedindo que ele seja incrementado novamente 
            }
        }
        pthread_mutex_unlock(&mutex); //libera o acesso ao contador para as demais threads
    }
    pthread_exit(NULL); //encerra a thread
}
int main()
{
    int n;
    scanf("%d", &n); //recebe a quantidade de threads a serem criadas do usuario
    pthread_t thread[n];
    int *id[n]; //vetor para guardar o id de cada thread
    int t;
    int rc;
    for (t = 0; t < n; t++)
    {
        id[t] = (int *)malloc(sizeof(int));
        *id[t] = t;                         
        printf("criando %d\n", *id[t]);
        rc = pthread_create(&thread[t], NULL, inc, (void *)id[t]);
        if (rc)
        {
            printf("ERRO; codigo de retorno eh %d\n", rc);
            exit(-1);
        }
    }
    int k;
    for (k = 0; k < n; k++)
    {
        pthread_join(thread[k], NULL); //faz com que a main aguarde a conclusao de todas threads
    }
    int h;
    for (h = 0; h < n; h++)
    {
        free(id[h]);
    }
    pthread_exit(NULL); 
}