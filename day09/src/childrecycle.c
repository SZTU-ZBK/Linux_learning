#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
void sys_error(char *str)
{
	perror(str);
	exit(1);
}
void catch_child(int signum)
{
	pid_t pid;
	while((pid=waitpid(-1,NULL,WNOHANG))>0)
	{
		printf("recycle the child process %d\n",pid);
	}
}

int main(int argc,char *argv[])
{
	pid_t pid;
	int i,ret;
	sigset_t set,oldset;
	sigemptyset(&set);
	sigaddset(&set,SIGCHLD);
	ret = sigprocmask(SIG_BLOCK,&set,&oldset);
	if(ret == -1)sys_error("sigprocmask error!");
	
	for(i=0;i<15;++i)
	{
		if((pid = fork())==0)
			break;
	}
	if(i==15)
	{
		struct sigaction act;
		act.sa_handler = catch_child;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;
		sigaction(SIGCHLD,&act,NULL);
		ret = sigprocmask(SIG_UNBLOCK,&set,&oldset);
		printf("I'm parent,pid = %d\n",getpid());
		while(1);
	}
	else
	{
		printf("I'm child pid = %d\n",getpid());
		return 1;
	}
	return 0;
}
