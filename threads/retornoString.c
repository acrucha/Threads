#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 5

void *PrintHello(void *threadid)
{
	int *tid = (int *)threadid;
	char *ret = (char *)malloc(1000);

	sprintf(ret, "Olá, mundo! Sou eu, a thread %d", *tid);
	pthread_exit((void *)ret);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int *taskids[NUM_THREADS];
	int t;
	int u;

	for (t = 0; t < NUM_THREADS; t++)
	{
		printf("Na main: criando thread %d\n", t);
		taskids[t] = (int *)malloc(sizeof(int));
		*taskids[t] = t;
		pthread_create(&threads[t], NULL, PrintHello, (void *)taskids[t]);
	}

	for (u = 0; u < NUM_THREADS; u++)//faço a main esperar por cada uma das threads ser concluída pra poder printar o valor que elas retornam
	{
		char *res;
		pthread_join(threads[u], ((void **)&res));
		printf("%s\n", res);
	}

	pthread_exit(NULL);
}

//além de retornar o valor inteiro da indentificação da thread, retonrar a string