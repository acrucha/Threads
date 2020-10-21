#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
1. recebe do usuario todos os dados
2. criar uma matriz[n][] com o nome de cada arquivo (receber)
3. criar 
*/

typedef struct matriz{
    int id;
    char linha[10];
}matriz;
void criouThread(int rc);
void lerArquivos(int n, char *nomesArq[]);

int main()
{
    //tem que ler tudo do usuário
    //threads, linhas e arquivos
    int n; //numero de arquivos
    int t; //numero de threads (tem que ser <= arquivos)
    int l; //numeros de linhas
    
    while (1)
    {
        printf("Quantidade de arquivos: ");
        scanf("%d", &n);
        printf("\nQuantidade de linhas: ");
        scanf("%d", &l);
        printf("\nQuantidade de threads: ");
        scanf("%d", &t);
        if (t <= n)
            break;
    }
    //se isso nao funcionar
    char *nomesArq[n]; //vetor de nomes dos arquivos
    /*int k;
    for(k = 0;k < n; k++){
        scanf(" %s", *(nomesArq+k));
    }*/
    *(nomesArq+0) = "a.txt";
    *(nomesArq+1) = "b.txt";
    lerArquivos(n, nomesArq);
    
    pthread_t thread[t]; //declaro as threads
    int i;
    
//     pthread_mutex_t mymutex[l]; //criando array de mutex pras l
//     for (i = 0; i < l; i++)
//         pthread_mutex_init(&mymutex[i], NULL); //função de inicializar mutex
//     int j, rc;
//     for (j = 0; j < t; t++)
//     {
//         rc = pthread_create(&thread[j], NULL, inc, (void *)arquivo);
//         criouThread(rc);
//         rc = pthread_create(&thread[j], NULL, inc, (void *)arquivo);
//         criouThread(rc);
//     }
}

int threadFunction(void *arq){
    int acabeiArquivo = 0;

    while(!acabeiArquivo){
        //ler arquivo
        
        //tentar fazer a alteração
            //se sim, entrar no mutex e travar a linha

            //se não, dormir até conseguir entrar (no caso rodar de novo esse while)
        //caso o arquivo termine, alterar acabeiArquivo para 1;
    }

    return acabeiArquivo; // receber essa resposta na main, caso em algum momento uma thread terminar de ler o arquivo dela, passa para outro arquivo 
}

void criouThread(int rc)
{
    if (rc)
    {
        printf("ERRO; codigo de retorno eh %d\n", rc);
        exit(-1);
    }
}


void lerArquivos(int n, char *nomesArq[]){
    FILE *arquivos[n];
    int i;    
    char linha[2];
    char texto[20];
    for(i = 0; i < n; i++){
        arquivos[i] = fopen(nomesArq[i], "r");
        if (arquivos[i] == NULL)
        {
            printf("Problemas na abertura do arquivo %s\n", nomesArq[i]);
        }else
        {
            printf("Abri arquivo %s\n", nomesArq[i]);
        }
        //while(fgets(texto, 20, arquivos[i]) != NULL) printf("\n%s", texto);
        fgets(linha, 1, arquivos[i]);
        printf("%s", linha);
        fgets(texto, 20, arquivos[i]);
        printf("\n%s", texto);
    }
}

/*
fseek(arq, 0, SEEK_END); //anda o cursor do arquivo ate o final dele
    //rewind();

    int qtdBytes = ftell(arq); //conta quantos bytes tem o arquivo

    int qtdAlunos = qtdBytes / sizeof(Aluno);

    rewind(arq); //===> volta o cursor pro começo do arquivo

    fread(alunos, sizeof(Aluno), 19, arq);
*/