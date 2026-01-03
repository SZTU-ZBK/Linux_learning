#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}
int main(int argc,char * argv[])
{
	int ret;
	int fd[2];
	pid_t pid;
	char *str = "hello pipe\n";
	ret = pipe(fd);
	if(ret == -1)sys_err("pipe error");
	pid = fork();
	if(pid > 0)
	{
		close(fd[0]);
		write(fd[1],str,strlen(str));
		close(fd[1]);
	}
	else if(pid == 0)
	{
		char buf[1024];
		close(fd[1]);
		int n = read(fd[0],buf,sizeof(buf));
		//write(1,buf,strlen(buf));
		write(1,buf,n); //这里应该用n，因为读取到的buf不会带有'/0'
		close(fd[0]);
	}
	return 0;
}

