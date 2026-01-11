#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
struct mystruct{
	int var;
	char *str;
};
void sys_error(char *str)
{
	perror(str);
	exit(1);
}
void *tfn(void *arg)
{
	struct mystruct *st = malloc(sizeof(*st));//注意，这里必须分配内存，不能返回局部变量，另外sizeof的参数要注意用*st，st是指针，语义上只会返回8字节大小的空间
	st->var = 100;
	st->str = "Hello world!";
	return (void *)st;
}
int main(int argc,char *argv[])
{
	pthread_t tid;
	struct mystruct *retval;
	int ret = pthread_create(&tid,NULL,tfn,NULL);
	if(ret != 0) sys_error("pthread error!");
	ret = pthread_join(tid,(void **)&retval);
	if(ret != 0) sys_error("pthread join error!");
	printf("child thread exit with var=%d,str=%s\n",retval->var,retval->str);
	return 0;
}
