#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
pthread_mutex_t mutex;
pthread_mutex_t mutex1;
void *tfn(void *arg)
{
	srand(time(NULL));
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("hello ");
		sleep(rand()%2);
		pthread_mutex_lock(&mutex1);
		printf("world\n");
		pthread_mutex_unlock(&mutex);
		pthread_mutex_unlock(&mutex1);
		sleep(rand()%2);
	}
	return NULL;
}
void sys_error(int ret,char *str)
{
	fprintf(stderr,"%s:%s\n",str,strerror(ret));
	exit(1);
}
int main(void)
{
	pthread_t tid;
	srand(time(NULL));
	int ret = pthread_mutex_init(&mutex,NULL);
	if(ret != 0)sys_error(ret,"mutex_init_error");
	ret = pthread_mutex_init(&mutex1,NULL);
	if(ret != 0)sys_error(ret,"mutex_init_error");
	pthread_create(&tid,NULL,tfn,NULL);
	while(1)
	{

		pthread_mutex_lock(&mutex1);
		printf("HELLO ");
		sleep(rand()%2);
		pthread_mutex_lock(&mutex);
		printf("WORLD\n");	
		pthread_mutex_unlock(&mutex);
		pthread_mutex_unlock(&mutex1);
		sleep(rand()%2);
	}
	pthread_mutex_destroy(&mutex);
	return 0;
}
