#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
void * callback(void *arg)
{
	pthread_t thread_num;//这个是线程的句柄，不是线程ID
	thread_num = pthread_self();
	printf("child thread pid = %d,tid = %lu\n",getpid(),thread_num);
	return NULL;
}
int main(int argc,char *argv[])
{
	pthread_t thread_num,thread_num_1;//这个是线程的句柄，不是线程ID
	thread_num = pthread_self();
	printf("main pid = %d,tid = %lu\n",getpid(),thread_num);
	int ret = pthread_create(&thread_num_1,NULL,callback,NULL);
	if(ret == -1)printf("pthread_create error%s\n",strerror(ret));
	ret = pthread_detach(thread_num_1);
	if(ret == -1)printf("pthread_detach error%s\n",strerror(ret));
	sleep(3);
	ret = pthread_join(thread_num_1,NULL);
	if(ret != 0)printf("pthread_join error%s\n",strerror(ret));
	return 0;
}
