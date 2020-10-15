#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_msg(void *ptr);

main()
{
  pthread_t thread1, thread2; //crio duas threads
  char *msg1 = "Thread 1";//atribuo mensagens a elas (os 'ids')
  char *msg2 = "Thread 2";
  int ret1 = pthread_create(&thread1, NULL, print_msg, (void *)msg1);//crio as threads
  int ret2 = pthread_create(&thread2, NULL, print_msg, (void *)msg2);
  pthread_join(thread1, NULL); //faço main esperar pela conclusão da thread 1, ou seja ela só printa o thread 1 voltou se realmente tiver voltado
  //OBS o join eh usado pra fazer esperar pthread_join(thread que eu to esperando, valor que essa thread vai retornar)
  printf("Thread 1 voltou: %d\n", ret1);
  pthread_join(thread2, NULL); //faço main esperar pela thread 2
  printf("Thread 2 voltou: %d\n", ret2);
  exit(0);
}

void *print_msg(void *ptr)
{
  char *message;
  message = (char *)ptr;
  printf("%s \n", message);
  pthread_exit(NULL);
}
