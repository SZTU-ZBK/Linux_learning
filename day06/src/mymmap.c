#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
void sys_error(char * str)
{
	perror(str);
	exit(1);
}
int var = 100;
int main(int argc,char *argv[])
{
	int fd;
	int *p;
	pid_t pid;
	fd = open("testmmap",O_RDWR|O_CREAT,0644);
	if(fd == -1) sys_error("mmap error!");
	ftruncate(fd,1024);
	p = (int *)mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(p == MAP_FAILED)
	{
		sys_error("mmap error!");
	}
	close(fd);
	pid = fork();
	if(pid == 0)
	{
		*p =7000;
		var = 1000;
		printf("child process:*p=%d,var=%d\n",*p,var);
	}
	else if(pid>0)
	{
		wait(NULL);		
		printf("parent process:*p=%d,var=%d\n",*p,var);
	}
	else
	{
		sys_error("fork error!\n");
	}
	return 0;
}

