#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#include <stdlib.h>
int queue[5];
#define NUM 5
sem_t blank_number,product_number;
//如果是多个线程的话，就需要加锁，否则无法保证资源不被同时访问
void *producer(void * arg)
{
	int i=0;
	while(1){
		sem_wait(&blank_number);
		queue[i] = rand()%1000+1;
		printf("----Produce---%d\n",queue[i]);
		sem_post(&product_number);
		i = (i+1)%NUM;
		sleep(1);
	}
}
void *consumer(void *arg)
{
	int i = 0;
	while(1){
		sem_wait(&product_number);
		printf("-Consume---%d\n",queue[i]);
		queue[i]=0;
		sem_post(&blank_number);
		i = (i+1)%NUM;
		sleep(2);
	}
}
int main(int argc,char *argv[])
{
	pthread_t pid,cid;
	sem_init(&blank_number,0,NUM);
	sem_init(&product_number,0,0);
	pthread_create(&pid,NULL,producer,NULL);
	pthread_create(&cid,NULL,consumer,NULL);
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);
	sem_destroy(&blank_number);
	sem_destroy(&product_number);
	return 0;
}

