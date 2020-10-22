#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Matriz
{
    char linha; //numero da linha
    char texto[25];
} Matriz;

void criouThread(int rc);
void lerArquivos(int n, char *nomesArq[]);

int main()
{
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
    char *nomesArq[n]; //vetor de nomes dos arquivos (também recebe do usuário?)
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
    int qtdViagens; //quantas viagens de trem tem em cada arquivo
    int qtdBytes;   //quantos bytes tem em cada arquivo
    int i;
    Matriz *viagensInfo[n]; //matriz com todas as viagens, linhas = qtd de arquivos, colunas = qtd de viagens de cada arquivo
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
        fseek(arquivos[i], 0, SEEK_END);                                      //move cursor pro fim do arquivo
        qtdBytes = ftell(arquivos[i]);                                        //conta quantos bytes tem até o fim do arquivo
        qtdViagens = qtdBytes / sizeof(Matriz);                               //quantidade de viagens
        viagensInfo[i] = (Matriz *)malloc((qtdViagens + 1) * sizeof(Matriz)); //alocando memória para o vetor de viagens
        if (viagensInfo[i] == NULL)
            exit(-1);
        rewind(arquivos[i]); //voltando cursor para o começo do arquivo
        int j = 0;
        char branco;
        for (j = 0; j < qtdViagens; j++)
        {
            fscanf(arquivos[i], " %c", &viagensInfo[i][j].linha);
            fscanf(arquivos[i], " %c", &branco);
            fscanf(arquivos[i], " %[^\n]", viagensInfo[i][j].texto);
        }
        int k = 0;
        for (k = 0; k < qtdViagens; k++)
        {
            printf("linha %c\ntexto:%s\n", viagensInfo[i][k].linha, viagensInfo[i][k].texto);
        }
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

/* while ((k < qtd) && (!feof(arquivos[i])))
        {
            fscanf(arquivos[i], "%c\n%[^\n]", &viagensInfo[i][k].linha, viagensInfo[i][k].texto);
            ++k;
        }*/
        // for(k = 0; k < qtd+1; k++){
        //     fread(viagensInfo[i][k], sizeof(Matriz), 1, arquivos[i]); //salva em viagensInfo
        // }
        // printf("Arquivo %d\n\n", i + 1);