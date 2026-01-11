#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}
void * callback(void *arg)
{
	pthread_t thread_num;//这个是线程的句柄，不是线程ID
	thread_num = pthread_self();
	while(1)
	{
		printf("child thread pid = %d,tid = %lu\n",getpid(),thread_num);
		sleep(1);
	}
	return NULL;
}
int main(int argc,char *argv[])
{
	pthread_t thread_num,thread_num_1;//这个是线程的句柄，不是线程ID
	void *tret = NULL;
	thread_num = pthread_self();
	printf("main pid = %d,tid = %lu\n",getpid(),thread_num);
	int ret = pthread_create(&thread_num_1,NULL,callback,NULL);
	if(ret == -1) perror("pthread error!");
	sleep(3);
	pthread_cancel(thread_num_1);//只有到达取消点（内核态）才能杀死线程，否则杀不死
	pthread_join(thread_num_1,&tret);
	printf("thread exit code is %d\n",(int ) tret);
	return 0;
}
