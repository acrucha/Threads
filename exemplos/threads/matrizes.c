#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 9
#define LINHAS 3
#define COLUNAS 3

int matriz1[3][3] = {{1, 2, 5}, {3, 4, 2}, {5, 6, 1}};
int matriz2[3][3] = {{1, 2, 5}, {3, 4, 2}, {5, 6, 1}};
int resultado[3][3];

// typedef struct Posicao
// {
//     int linha;
//     int coluna;
// } Posicao;

void *threadCode(void *tid)
{
    //puts ("a");
    int threadId = (*(int *)tid);
    int i, j, z = 0, coluna, linha;
    for (i = 0; i < LINHAS && z < threadId; i++)
    {
        for (j = 0; j < COLUNAS && z < threadId; j++)
        {
            coluna = j;
            linha = i;
            z++;
            //puts ("loop");
        } 
    }
    int x;
    resultado[linha][coluna] = 0;
    for (x = 0; x < 3; x++)
    {
        //puts ("resultado");//por alguma razão ele fica preso aqui pra
       resultado[linha][coluna] += matriz1[linha][x]*matriz2[x][coluna];
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];
    int t, i, j, u;
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("No main: criando thread %d\n", t);
        taskids[t] = (int *)malloc(sizeof(int));
        *taskids[t] = t;
		pthread_create(&threads[t], NULL, threadCode, (void *)taskids[t]);
    }
    for (u = 0; u < NUM_THREADS; u++)
    {
        pthread_join(threads[u], NULL);
    }
    for (i = 0; i < LINHAS; i++)
	{
		for (j = 0; j < COLUNAS; j++)
		{
			printf("%d\t", resultado[i][j]);
		}
		printf("\n");
	}

}