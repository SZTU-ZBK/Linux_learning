#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sys_error(char * str)
{
	perror(str);
	exit(1);
}
int main(int argc,char *argv[])
{
	pid_t pid;
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1) sys_error("pipe error!");
	pid = fork();
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls","-l",NULL);
		sys_error("execlp ls -l error!");
	}
	else if(pid >0)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
		sys_error("execlp wc -l error!");
	}
	return 0;
}
