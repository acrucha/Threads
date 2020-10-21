#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
1. recebe do usuario todos os dados
2. criar uma matriz[n][] com o nome de cada arquivo (receber)
3. criar 
*/

typedef struct Matriz
{
    char linha; //numero da linha
    char texto[25];
} Matriz;

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

    *(nomesArq + 0) = "a.txt";
    *(nomesArq + 1) = "b.txt";
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

int threadFunction(void *arq)
{
    int acabeiArquivo = 0;

    while (!acabeiArquivo)
    {
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

void lerArquivos(int n, char *nomesArq[])
{ //recebe a matriz com nome de todos arquivos
    FILE *arquivos[n];
    int i, qtd;
    Matriz *viagensInfo[n]; //vetor com todas as viagens --> VETOR DE PONTEIROS, linhas = qtd de arquivos, colunas = qtd de viagens de cada arquivo
    for (i = 0; i < n; i++)
    {
        arquivos[i] = fopen(nomesArq[i], "r"); //abre arquivo com aquele nome

        if (arquivos[i] == NULL)
        {
            printf("Problemas na abertura do arquivo %s\n", nomesArq[i]);
        }
        else
        {
            printf("Abri arquivo %s\n", nomesArq[i]);
        }
        fseek(arquivos[i], 0, SEEK_END);   //move cursor pro fim do arquivo
        int qtdBytes = ftell(arquivos[i]); //conta quantos bytes tem até o fim do arquivo
        // printf("qtd bytes = %d\n", qtdBytes);
        // printf("sizeof matriz = %ld\n", sizeof(Matriz));
        qtd = qtdBytes / sizeof(Matriz); //quantidade de viagens
        // printf("qtd viagens = %d\n", qtd);
        viagensInfo[i] = (Matriz *)malloc((qtd + 1) * sizeof(Matriz)); //alocando memória para o vetor de viagens

        if (viagensInfo[i] == NULL)
            exit(-1);

        rewind(arquivos[i]); //voltando cursor para o começo do arquivo
        int k;
        while(fread(viagensInfo[i], sizeof(Matriz), qtd, arquivos[i])){
            printf("%c\n %s\n",viagensInfo[i]->linha,viagensInfo[i]->texto);
        }
        /* while ((k < qtd) && (!feof(arquivos[i])))
        {
            fscanf(arquivos[i], "%c %[^\n]", &viagensInfo[i][k].linha, viagensInfo[i][k].texto);
            ++k;
        }*/
        // for(k = 0; k < qtd+1; k++){
        //     fread(viagensInfo[i][k], sizeof(Matriz), 1, arquivos[i]); //salva em viagensInfo
        // }
        // printf("Arquivo %d\n\n", i + 1);
       printf("%s\n", viagensInfo[i][k].texto);
    }
    /*int j;
    for(j = 0; j < qtd; j++){
        free(viagensInfo[j]);
    }
    for(j = 0; j < n; j++){
        fclose(arquivos[j]);
    }*/
}

/*
TENTATIVAS SEM SUCESSO:

 while ((k < qtd) && (!feof(arquivos[i])))
        {
            fscanf(arquivos[i], "%c %[^\n]", &viagensInfo[i][k].linha, viagensInfo[i][k].texto);
            ++k;
        }
        
for(k = 0; k < qtd+1; k++){
            fread(&(viagensInfo[i][k].linha), 1, 1, arquivos[i]); //salva em viagensInfo
            fread(viagensInfo[i][k].texto, 25, 1, arquivos[i]); //salva em viagensInfo
        }
*/