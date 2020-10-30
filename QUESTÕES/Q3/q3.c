#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char s1[100];
char s2[100];
int p;
int contador = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* search(void *argumento){ //procura s2 dentro de s1
    int valor = *(int*)argumento;
    int tamanho1 = strlen(s1);
    int tamanho2 = strlen(s2);
    int i,k,j,flag;
    //pthread_mutex_lock(&mutex);
    for(i=0+valor;i<tamanho1;i=i+p){ // esse for eh p procurar a s2
        flag=0;
        k=i;
        for(j=0;j<tamanho2;j++){
            if(s2[j]==s1[k]){
                k++;
            }
            else{
                flag=1;
                break;
            }
        }
        if(flag==0){
            pthread_mutex_lock(&mutex);
            contador++;
            pthread_mutex_unlock(&mutex);
        }
    }
    //pthread_mutex_unlock(&mutex);
}

int main(){
    int somador = 0; 
    int n1, n2, i;
    scanf(" %[^\n]",s1);
    scanf(" %[^\n]",s2);
    n1 = strlen(s1);
    n2 = strlen(s2);
    for(i=n1;i>0;i--){   //rever isso depois c as meninas
        if(n1%i == 0 && n2 < n1/i){
            p=i;
            break;
        }
    }
    int x[p]; 
    for (int a = 0; a < p; a++){
        x[a] = a;
    } 
    int t;
    int status;
    pthread_t thread[p];
    for (t = 0; t < p; t++){
        status = pthread_create(&thread[t], NULL, search, (void *)&x[t]);
        if (status){
            printf("ERRO; codigo de retorno eh %d\n", status);
            exit(-1);
        }
    }
    for (i = 0; i < p; i++) {
        pthread_join(thread[i], NULL); 
    }
    // for (i = 0; i < p; i++){
    //     somador = somador + contador[i];  
    // }
    printf("%d\n",contador);
    return 0;
}

