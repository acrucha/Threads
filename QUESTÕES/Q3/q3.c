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
    for(i=0+valor;i<tamanho1;i=i+p){ //o i começa pelo id de cada thread e varia de acordo com a quantidade de threads
        flag=0;
        k=i;
        for(j=0;j<tamanho2;j++){//roda um for com o tamanho da string 2
            if(s2[j]==s1[k]){//verifica se a partir da posição k da string 1 vai ser igual a string 2 
                k++;//varia o k para mudar a posição para a próxima comparação
            }
            else{//caso em algum momento da execução do for o if não for executado, ele termina a validação para aquela thead e da um break.
                flag=1;
                break;
            }
        }
        if(flag==0){//caso ele não mude a flag( ele encontrou a string 2 na string 1)
            pthread_mutex_lock(&mutex);
            contador++;//aumenta o contador em 1 para cada ve que isso ocorre.
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
    for(i=n1;i>0;i--){   //Implelemtado as condições impostas para o número p
        if(n1%i == 0 && n2 < n1/i){// escolhe o maior npumero possível para p, vito que, o for é reverso.
            p=i;
            break;
        }
    }
    int x[p];//vetor contendo o id de cada thread
    for (int a = 0; a < p; a++){
        x[a] = a;
    } 
    int t;
    int status;
    pthread_t thread[p];
    for (t = 0; t < p; t++){//cria as threads 
        status = pthread_create(&thread[t], NULL, search, (void *)&x[t]);
        if (status){//verifica se foi inicislizada
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

