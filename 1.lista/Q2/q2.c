#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Info {
    int id;
    char frase[20];
} Info;

// void lerArquivo ()
// {
//     int i;
//     char linha[30];
//     for (i = 0; i <; i++)
//     {
        
//     }
// }

int main()
{
    int qtd_threads;
    int qtd_arq = 2;
    while (1){
        printf ("Quantidade de threads: ");
        scanf ("%d", &qtd_threads);
        if (qtd_threads <= qtd_arq) break;
    }
    //abri os arquivos
    FILE *arquivo = fopen("a.txt", "rt");
    FILE *arquivo2 = fopen("b.txt", "rt");
    pthread_t thread[qtd_threads];
    Info *linha[qtd_threads]; //aqui é teste
    linha->
    int t;
    for (t = 0; t < qtd_threads; t++)
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
    
}