#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	printf("before fork 1~\n");
	printf("before fork 2~\n");
	printf("before fork 3~\n");
	pid_t pid;
	pid = fork();
	if(pid == -1)
	{
		perror("fork error!");
		exit(1);
	}
	else if(pid == 0)
	{
		printf("child_process:---child is created!\n");
		printf("child_process:pid=%d,ppid=%d\n",getpid(),getppid());
	}
	else
	{
		printf("parent_process:the pid of child process is %d\n",pid);
		printf("parent_process:pid=%d,ppid=%d\n",getpid(),getppid());
	}
	printf("============end of file\n");
	return 0;
}

