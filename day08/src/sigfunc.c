#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void print_set(const sigset_t * set)
{
	for(int i=0;i<32;++i)
	{
		if(sigismember(set,i))
		{
			putchar('1');
		}else
		{
			putchar('0');
		}
	}
	printf("\n");
}
void sys_error(char * str)
{
	perror(str);
	exit(1);
}
int main(int argc,char *argv[])
{
	sigset_t set,oldset,pedset;
	int ret = 0;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	ret = sigprocmask(SIG_BLOCK,&set,&oldset);
	if(ret == -1)sys_error("sigprocmask error!");
	while(1)
	{
		ret = sigpending(&pedset);
		if(ret == -1) sys_error("sigpending error!");
		print_set(&pedset);
		sleep(1);
	}
	return 0;
}


