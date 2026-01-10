#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int main(int argc,char *argv[])
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		sleep(5);	
		kill(getppid(),SIGSEGV);
		while(1)
		{
			sleep(1);
			printf("I'm child process,pid=%d\n",getpid());
		}
	}
	else if(pid>0)
	{
		while(1)
		{
			sleep(1);
			printf("I'm parent process,pid=%d\n",getpid());
		}
	}
	return 0;
}
