#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long contador = 0;
int flag=0;
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER; //mutex estático

void *inc(void *threadid)
{
    while(flag==0){
        pthread_mutex_lock(&mymutex);
        if(contador<1000000){
            contador++;
            if(contador==1000000){
                int tid = *((int *)threadid);
                printf("o valor é %ld \n",contador);
                printf("a thread é %d \n",tid);
                flag=1;
            }
        }
        pthread_mutex_unlock(&mymutex);
    }
    pthread_exit(NULL);
}
int main(/*int argc, char *argv[]*/)
{
    int n;
    scanf("%d",&n);
    pthread_t thread[n];
    int *id[n];
    int t;
    int rc;
    for (t = 0; t < n; t++) //rodo o array
    {
        id[t] = (int *)malloc(sizeof(int)); //pra cada posição, eu aloco
        *id[t] = t; //e digo q o valor é igual a esse número
        printf("criando %d\n",*id[t]);
        rc=pthread_create(&thread[t], NULL, inc, (void *)id[t]); //aqui o argumento da função é justamente aquele valr q eu dei
        if(rc){
            printf("ERRO; codigo de retorno eh %d\n", rc);
            exit(-1);
        }
    }
    int k;
    for(k=0;k<n;k++){
        pthread_join(thread[k],NULL);
    }
    pthread_exit(NULL);
    int h;
    for(h=0;h<n;h++){
        free(id[h]);
    }
}