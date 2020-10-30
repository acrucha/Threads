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

void lerArquivos();

int matriz[3][6] = {255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 0, 255, 255, 255, 0, 0, 0};
Pixel *pixels; //vetor que vai guardar todos os pixels (vai ser alocado na funcao de )
int colunas, linhas;
int qtdThreads;
char max[3] = {}; 
int matriz_saida[3][2]; //botei um num aleatorio

//C =  R*0.30 + G*0.59 + B*0.11
/*void *calculadora(void *argumento){//o tamanho da matriz qu eu recebo tem o mesmo 
tamanho da matriz de saida ? essa é a minha duvida pq eu acho que são diferentes o numero 
de linhas, visto que, cada linha da matriz recebida representa um pixel na matriz final, 
então se eu recebi que a matriz de saida vai possuir 3 colunas e duas linhas dando um total 
de 6 pixeis então eu tenho que receber um total de 18 elementos de uma matriz*/
/*
    int valor= *(int*)argumento;
    int r,g,b;
    int vetor[6];
    for(int i=0;i<6;i++){
        int k;
        r=matriz[i][k]*0.30;
        g=matriz[i][k]*0.59;
        b=matriz[i][k]*0.11;
        vetor[i]+=b,r,g;
    }
    int k;
    int contador=0;
    for(k=0;k<linhas;k++){
        int i;
        for(i=0;i<colunas;i++){
            matriz_saida[k][i]=vetor[contador];
            contador++;
        }
    }
}*/
int main()
{
    //ler arquivo
    qtdThreads = linhas;
    int i, rc;
    lerArquivos();
    /*pthread_t threads[qtdThreads]; //declarando vetor com todas as threads
    int x[qtdThreads]; 
    for (int a = 0; a < qtdThreads; a++){
        x[a] = a;
    } 
    for (i = 0; i < qtdThreads; i++){
        rc = pthread_create(threads[i], NULL, calculadora, (void*)&x[i]);
        if(rc){
            printf("erro!!");
            exit(-1);
        }
    }
    for (i = 0; i < qtdThreads; i++){
        pthread_join(threads[i], NULL);
    }
    arqSaida();*/
    return 0;
}

// a qtd de elementos da matriz que foi pegada no arquivo é linhas vs colunas?

//matirz pegada do arquivo

void lerArquivos()
{
    FILE *arquivo;
    arquivo = fopen("img.txt", "r"); //mas na vdd é pra ler como se fosse BIINARIO
    if (arquivo != NULL)
    {
        puts("Li ArQuIVo");
        fseek(arquivo, 0, SEEK_END); //move cursor pro fim do arquivo
        int qtdBytes = ftell(arquivo);
        int qtd = qtdBytes / sizeof(Pixel);
        rewind(arquivo);
        char c, aux[3], cS[2]; //criação de variáveis auxiliares
        int lAtual = 0, colAtual = 0, p3 = 0, i = 0;
        char cl[3][2];
        for(i = 0; i < 2; i++){ // roda 2 vezes pq na primeira le o p3 e a coluna e na segunda le a linha
            //lendo cada string
            if(p3 == 0){ //li p3 e \n
                fread(aux, sizeof(char), 3, arquivo);
                puts("li modo");
                p3 = 1; // ja li p3 -> avisando
            }
            while((cS[0] = fgetc(arquivo)) != ' '){
                //ler linha e coluna
                if(cS[0] == '\n') break; 
                else {
                    strcat(cl[i], cS);     
                    puts("li colunas e etc e tal");
                }           
            }
        } 
        printf("oi de mileto\n");
        while((cS[0] = fgetc(arquivo)) != '\n'){
            //ler max
            strcat(max, cS);
            puts("aqui"); 
        }
        colunas = atoi(cl[0]);
        printf("colunas = %d\n", colunas);
        linhas = atoi(cl[1]);
        printf("linhas = %d\n",linhas);
        int numPixels = colunas * linhas;
        pixels = (Pixel *) malloc(numPixels * sizeof(Pixel));
        i = 0;
        
        for (i = 0; i < numPixels;)
        {
            puts("vo ler os pixels");
            c = fgetc(arquivo);
            if (c == '\n') i++; //mudou de pixel
            else if (c != ' '){
                puts("vou ler ESSA MERDA");
                printf ("pixel:%d ", i+1);
                char aux[4];
                fread(aux, sizeof(char), 4, arquivo);
                pixels[i].r = atoi(aux);
                printf ("R:%d ", pixels[i].r);
                fread(aux, sizeof(char), 4, arquivo);
                pixels[i].g = atoi(aux);
                printf ("G:%d ", pixels[i].g);
                fread(aux, sizeof(char), 3, arquivo);
                pixels[i].b = atoi(aux);
                printf ("B:%d ", pixels[i].b);//GRANDE ACRUCHINHA11!!!!!!!!
            }
        }
        // for (i = 0; i < numPixels; i++)
        // {
        //     printf ("pixel: %d\nR:%d  G:%d  B:%d\n", i+1, pixels[i].r,pixels[i].g,pixels[i].b);
        // }
    fclose(arquivo);
    }
}
/*
P3
3 2 //seis pixels
255//achei o \n
255 0   0  //aqui é 1 pixel
0   255 0
0   0   255
255 255 0
255 255 255
0   0   0
*/
void *calculadora(void *argu){ //funcao que converte de RGB para cinza
    int i = *(int*)argu;
    int cinza;
    int r, g, b, j;
    r = pixels[i].r * 0.30;
    g = pixels[i].g * 0.59;
    b = pixels[i].b * 0.11;
    cinza = r + g + b;
    for (j=0;j<3; j++){
        matriz_saida[i][j] = cinza;
    }
}

void arqSaida(){ //funcao q converte a matriz de saida p um arquivo out
    FILE *arqOut; //criando
    arqOut = fopen("arquivo_saida.txt", "a"); //abrindo
    if(arqOut == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(-1);
    }
    int i;
    for(i=0;i<linhas;i++){ //escrevendo
        fprintf(arqOut, "%d %d %d\n", matriz_saida[i][0], matriz_saida[i][1], matriz_saida[i][2]);
        //aqui eu n tenho q mandar pular linha?
    }
    fclose(arqOut); //fechando
}

//fprintf(arqOut, "%s", palavra);
