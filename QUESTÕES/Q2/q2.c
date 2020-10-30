#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define NUM_ARQ 4
#define NUM_MAX_LINHAS 9

typedef struct Viagens
{
    char linha;
    char texto[28];
} Viagens;

Viagens *arqViagens[NUM_ARQ]; //matriz contendo todas as viagens de todos arquivos

char linhas[20];
char *nomesArq[NUM_ARQ]; //vetor de nomes dos arquivos
int qtdViagens = 0;
int l; //quantidade de linhas
int t; //quantidade de threads

static pthread_mutex_t mutex[NUM_MAX_LINHAS] =
    {
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER}; // constroi uma lista de mutexes de tamanho NUM_MAX_LINHAS, já que teremos 1 mutex para cada linha.

char telaInicial[NUM_MAX_LINHAS][28] =
    {
        "LWF783 Ingazeira    00:25",
        "SQG715 Oroco        02:25",
        "MTB948 Tracunhaem   02:45",
        "FPG132 Sanharo      04:45",
        "OAM825 Olinda       05:00",
        "LSP762 Camaragibe   07:45",
        "MHU190 Igarassu     11:20",
        "MVW574 Petrolina    11:35",
        "TLF175 Quixaba      12:15"}; //primeira tela a ser printada

void lerArquivos();
void *threadFunction(void *id);

int main()
{
    while (1) //recebendo entrada do usuário
    {
        printf("\nQuantidade de linhas: ");
        scanf("%d", &l);
        printf("\nQuantidade de threads: ");
        scanf("%d", &t);
        if (l > NUM_MAX_LINHAS)
            printf("\nQuantidade de linhas invalida");
        if (t > NUM_ARQ)
            printf("\nQuantidade de threads invalida");
        if (t <= NUM_ARQ && l <= NUM_MAX_LINHAS)
            break;
    }

    //nomeia cada arquivo
    *(nomesArq + 0) = "d.txt";
    *(nomesArq + 1) = "e.txt";
    *(nomesArq + 2) = "f.txt";
    *(nomesArq + 3) = "g.txt";

    lerArquivos(); //chama a funcao que le todos os arquivos e guarda em uma matriz

    pthread_t threads[t]; //eu crio um array com a quantidade de threads que eu quero
    int *id[t];           //guarda o id das threads
    int rc;               //para teste da criacao da thread
    int i;
    system("clear");
    for (i = 0; i < l; i++)
    {
        printf("\033[22;0m"); //boto a letra branca
        int cor = 100 + i;
        if (cor == 103 || cor == 107) //se a cor for amarela ou branca, muda a cor da letra para preto
            printf("\033[22;30m");
        else if (cor == 108)
            cor = 46; //se for linha 9, muda pra ciano
        printf("\033[22;%dm", cor);
        printf("%s\n", telaInicial[i]);
    }
    for (i = 0; i < t; i++)
    {
        id[i] = (int *)malloc(sizeof(int)); //pra cada posição, eu aloco
        *id[i] = i;
        rc = pthread_create(&threads[i], NULL, threadFunction, (void *)id[i]);
        if (rc)
        {
            printf("ERRO; codigo de retorno eh %d\n", rc);
            exit(-1);
        }
    }

    int j;
    for (j = 0; j < t; j++)
    {
        pthread_join(threads[j], NULL);
    }

    for (i = 0; i < NUM_ARQ; i++)
    {
        free(arqViagens[i]);
    }

    pthread_exit(NULL);
}

void *threadFunction(void *id)
{
    int i, k;
    int arqAtual = (*(int *)id);
    for (k = arqAtual; k < NUM_ARQ; k += t) //entre os arquivos
    {
        for (i = 0; i < qtdViagens; i++) //pra cada arquivo
        {
            int linha = arqViagens[k][i].linha - '1'; //transformando o char para o seu equivalente em int
            if (linha < l)
            {
                printf("\033[22;0m");              //mudo a cor da letra pra branco
                pthread_mutex_lock(&mutex[linha]); //se não puder modificar aquela linha, dormir até conseguir entrar
                printf("\033[%d;1H", linha + 1);   //mover cursor para a respectiva linha
                int cor = 100 + linha;
                if (cor == 103 || cor == 107) //se a cor for amarela ou branco, mudo a letra para preto
                    printf("\033[22;30m");
                else if (cor == 108)
                    cor = 46;                         //se for linha 9, muda pra ciano escuro
                printf("\033[22;%dm", cor);           //colorir a linha
                printf("%s", arqViagens[k][i].texto); //printa o texto
                sleep(2);                             // espera 2 segundos e libera o mutex
                pthread_mutex_unlock(&mutex[linha]);
            }
        }
    }
    pthread_exit(NULL);
}

void lerArquivos()
{
    int i;
    for (i = 0; i < NUM_ARQ; i++)
    {
        qtdViagens = 0;
        FILE *arquivo;
        arquivo = fopen(nomesArq[i], "r");

        if (arquivo != NULL)
        {
            fseek(arquivo, 0, SEEK_END); //move cursor pro fim do arquivo
            int qtdBytes = ftell(arquivo);
            int qtd = qtdBytes / sizeof(Viagens);

            arqViagens[i] = (Viagens *)malloc((qtd + 1) * sizeof(Viagens)); //alocando memória para o vetor de viagens
            if (arqViagens[i] == NULL)
                exit(-1);

            rewind(arquivo);
            int k = 0;
            char c, texto[28]; //criação de variáveis auxiliares

            while ((c = fgetc(arquivo)) != EOF)
            {
                if (k % 30 == 0)
                { //quer dizer que eu cheguei em uma nova viagem! é 30 porque conta o os \n + os 26 caracteres do texto
                    arqViagens[i][qtdViagens].linha = c;
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
        }
        fclose(arquivo);
    }
}