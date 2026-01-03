#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void sys_error(char * str)
{
	perror(str);
	exit(1);
}
int main(int argc,char *argv[])
{
	pid_t pid;
	int i = 0;
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1) sys_error("pipe error!");
	for(i = 0;i < 2;++i)
	{
		pid = fork();
		if(pid == 0)break;
	}
	if(i == 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls","-l",NULL);
		sys_error("execlp ls -l error!");
	}
	else if(i==1)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);//这里相当于不断read，只有read到EOF才会退出 
		sys_error("execlp wc -l error!");
	}
	else if(i == 2)
	{
		close(fd[0]);
		close(fd[1]);  //这里务必关闭管道的写端，否则wc的读端阻塞，数据都在缓冲区里出不来
		wait(NULL);
		wait(NULL);
	}
	return 0;
}
