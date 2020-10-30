#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct Pixel
{
    int r;
    int g;
    int b;
} Pixel; //estrutura pros pixels

void lerArquivos();            //le arquivo de entrada e guarda em um vetor de pixels
void *calculadora(void *argu); //funcao que converte de RGB para cinza
void arqSaida();               //printa a imagem convertida de RGB para cinza em um arquivo de saida

Pixel *pixels;       //vetor que vai guardar todos os pixels (vai ser alocado na funcao de )
int colunas, linhas; //guarda quantas linhas e colunas tem a imagem
int qtdThreads;      //é a mesma quantidade de pixels da imagem
int **matriz_saida;  //matriz que vai ser escrita ano arquivo de saida

int main()
{
    lerArquivos();
    pthread_t threads[qtdThreads]; //declarando vetor com todas as threads
    int *id[qtdThreads];           //vetor com o id de cada thread
    int i, rc;
    matriz_saida = (int **)malloc(qtdThreads * sizeof(int *)); //alocando a matriz de saida
    for (i = 0; i < qtdThreads; i++)
    {
        matriz_saida[i] = (int *)malloc(3 * sizeof(int)); //3 pq eh r g b
    }

    for (i = 0; i < qtdThreads; i++) //criacao das threads
    {
        id[i] = (int *)malloc(sizeof(int));
        *id[i] = i;
        rc = pthread_create(&threads[i], NULL, calculadora, (void *)id[i]);
        if (rc)
        {
            printf("ERRO\n");
            exit(-1);
        }
    }
    for (i = 0; i < qtdThreads; i++)
    {
        pthread_join(threads[i], NULL); //faz a main esperar por todas as threads
    }
    arqSaida();
    free(pixels);
    return 0;
}

void lerArquivos()
{
    char s[4]; //modo P3
    int i, j;
    int max;
    FILE *arq = fopen("img.txt", "r");
    if (arq == NULL)
    {
        printf("ERRO\n");
        exit(-1);
    }
    fscanf(arq, " %s", s); //le o modo (P3)
    fscanf(arq, "%d", &colunas);
    fscanf(arq, "%d", &linhas);
    qtdThreads = colunas * linhas; //vai ser criada uma thread para cada pixel
    fscanf(arq, "%d", &max);

    pixels = (Pixel *)malloc(qtdThreads * sizeof(Pixel));

    for (i = 0; i < qtdThreads; i++)
    {
        fscanf(arq, "%d", &pixels[i].r);
        fscanf(arq, "%d", &pixels[i].g);
        fscanf(arq, "%d", &pixels[i].b);
    }

    fclose(arq);
}

void *calculadora(void *argu)
{
    int i = (*(int *)argu); //o indice (o pixel) que a thread ira alterar é a do seu id
    int cinza;
    int r, g, b, j;
    r = pixels[i].r * 0.30;
    g = pixels[i].g * 0.59;
    b = pixels[i].b * 0.11;
    cinza = r + g + b;
    for (j = 0; j < 3; j++)
    {
        matriz_saida[i][j] = cinza; //os valores r, g e b serao os mesmos (cinza)
    }
}

void arqSaida()
{                                             //funcao q converte a matriz de saida p um arquivo out
    FILE *arqOut;                             //criando
    arqOut = fopen("arquivo_saida.txt", "w"); //abrindo
    if (arqOut == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        exit(-1);
    }
    int i;
    for (i = 0; i < qtdThreads; i++)
    {
        fprintf(arqOut, "%d %d %d\n", matriz_saida[i][0], matriz_saida[i][1], matriz_saida[i][2]);
    }
    fclose(arqOut); //fechando o arquivo
}
