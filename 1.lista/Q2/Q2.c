#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_ARQ 4
#define NUM_MAX_LINHAS 9

typedef struct Viagens
{
    char linha;
    char texto[28];
} Viagens;

Viagens *arqViagens[NUM_ARQ]; //matriz contendo todas as viagens de todos arquivos

char *nomesArq[NUM_ARQ]; //vetor de nomes dos arquivos
int qtdViagens = 0;
int l;    //quantidade de linhas
int t;    //quantidade de threads

static pthread_mutex_t mutex[NUM_MAX_LINHAS] =
  { P99_DUPL(NUM_MAX_LINHAS, PTHREAD_MUTEX_INITIALIZER) };  // constroi uma lista de mutexes de tamanho NUM_MAX_LINHAS, 
                                                            // já que teremos 1 mutex para cada linha.

void lerArquivos();
void threadFunction(void *id);

int main()
{
    while (1) //recebendo entrada do usuário
    {
        printf("\nQuantidade de linhas: ");
        scanf("%d", &l);
        printf("\nQuantidade de threads: ");
        scanf("%d", &t);
        if (l > 9)
            printf("\nQuantidade de linhas invalida");
        if (t > NUM_ARQ)
            printf("\nQuantidade de threads invalida");
        if (t <= NUM_ARQ && l <= NUM_MAX_LINHAS)
            break;
    }

    *(nomesArq + 0) = "d.txt";
    *(nomesArq + 1) = "e.txt";
    *(nomesArq + 2) = "f.txt";
    *(nomesArq + 3) = "g.txt";

    lerArquivos();

    int i;
    pthread_t threads[t]; //eu crio um array com a quantidade de threads que eu quero
    int *id[t];
    int rc;
    for (i = 0; i < t; i++)
    {
        id[i] = (int *)malloc(sizeof(int)); //pra cada posição, eu aloco
        *id[i] = i;
        printf("Na main: criando thread %d\n", i);
        rc = pthread_create(&threads[t], NULL, threadFunction, (void *)id[t]); //aqui o argumento da função é justamente aquele valr q eu dei
        if (rc)
        {
            printf("ERRO; codigo de retorno eh %d\n", rc);
            exit(-1);
        }
    }

    for (i = 0; i < NUM_ARQ; i++)
    {
        free(arqViagens[i]);
    }

    return 0;
}

void threadFunction(void *id)
{
    int i, k, sair = 0;
    
    int arqAtual = ((int *) id);
    
    for (k = arqAtual; k < NUM_ARQ; k += t) //entre os arquivos
    {
        for(i = 0; i < qtdViagens; i++) //pra cada arquivo
        {
            //tenta acessar a linha
            int linha = arqViagens[k][i].linha - '1'; //transformando o char para o seu equivalente em int
            if (linha <= l)
            {
                pthread_mutex_lock(&mutex[linha]);        //se não, dormir até conseguir entrar
                //entrei no mutex
                    //altera a tela
                    printf("%s", arqViagens[k][i].texto); //adequar a linha
                    // espera 2 segundos e libera o mutex

                pthread_mutex_unlock(&mutex[linha]);
            }
        }
        //terminei de ler arquivo

    }
    
    //tentar fazer a alteração

    
    //caso o arquivo termine, alterar acabeiArquivo para 1;
    // receber essa resposta na main, caso em algum momento uma thread terminar de ler o arquivo dela, passa para outro arquivo
}

void lerArquivos()
{
    int i;
    for (i = 0; i < NUM_ARQ; i++)
    {
        FILE *arquivo;
        arquivo = fopen(nomesArq[i], "r");

        if (arquivo != NULL)
        {

            printf("\nAbri arquivo %s!!!\n\n", nomesArq[i]);

            fseek(arquivo, 0, SEEK_END); //move cursor pro fim do arquivo
            int qtdBytes = ftell(arquivo);
            int qtd = qtdBytes / sizeof(Viagens);

            arqViagens[i] = (Viagens *) malloc((qtd + 1) * sizeof(Viagens)); //alocando memória para o vetor de viagens
            if (arqViagens[i] == NULL)
                exit(-1);

            rewind(arquivo);
            int k = 0;
            char c, texto[28], linhas[20]; //criação de variáveis auxiliares

            while ((c = fgetc(arquivo)) != EOF)
            {
                if (k % 30 == 0)
                { //quer dizer que eu cheguei em uma nova viagem! é 30 porque conta o os \n + os 26 caracteres do texto
                    linhas[qtdViagens] = c;
                    qtdViagens++; //sempre aumentando depois que chega uma nova linha
                }
                k++; //varre os caracteres, ou seja, conta quantos tem.
            }
            rewind(arquivo); //retorna para o início do arquivo
            qtdViagens = 0;  //zerando novamente
            while ((c = fgetc(arquivo)) != EOF)
            {
                if (c == '\n')
                {
                    fread(texto, sizeof(char), 27, arquivo); //lê cada nova viagem e guarda --> 27 = 26msg + \n
                    strcpy(arqViagens[i][qtdViagens].texto, texto);
                    qtdViagens++;
                }
            }

            // k = 0;
            // for (k = 0; k < qtdViagens; k++)
            // {
            //     arqViagens[i][k].linha = linhas[k];
            //     printf("%c\n", arqViagens[i][k].linha);
            //     printf("%s", arqViagens[i][k].texto);
            // }
        }
        fclose(arquivo);
    }
}