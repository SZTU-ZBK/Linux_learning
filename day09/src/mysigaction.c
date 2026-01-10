#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void sys_error(char * str)
{
	perror(str);
	exit(0);
}
void sig_catch(int signo)
{
	printf("catch you! %d\n",signo);
	return ;
}
int main(int argc,char * argv[])
{
	struct sigaction act,oldact;
	act.sa_handler = sig_catch;
	sigemptyset(&(act.sa_mask));
	act.sa_flags = 0;
	int ret = sigaction(SIGINT,&act,&oldact);
	if(ret == -1) sys_error("sigaction error!\n");
	while(1);
	return 0;
}


