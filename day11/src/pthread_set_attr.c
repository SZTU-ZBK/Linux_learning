#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

void sys_err(char *str,int ret)
{
	if(ret!=0)
	{
		fprintf(stderr,"%s:%s\n",str,strerror(ret));
		exit(1);
	}
}
void *tfn(void *arg)
{
	printf("I'm child pthread!\n");
	return NULL;
}
int main(int argc,char *argv[])
{
	pthread_attr_t attr;
	pthread_t tid;
	int ret = pthread_attr_init(&attr);
	sys_err("attr_init_error",ret);
	ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);	
	sys_err("attr_init_error",ret);
	ret = pthread_create(&tid,&attr,tfn,NULL);
	sys_err("attr_init_error",ret);
	ret = pthread_attr_destroy(&attr);	
	sys_err("attr_init_error",ret);
	ret = pthread_join(tid,NULL);
	sys_err("pthread_join_error",ret);
	return 0;
}

