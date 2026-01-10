#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}
int main(int argc,char *argv[])
{
	pid_t pid;
	int ret;
	pid = fork();
	if(pid>0)exit(0);
	pid = setsid();
	if(pid == -2) sys_err("setsid error");
	ret = chdir("/home/zbk/");
	if(ret == -1)sys_err("chdir error");
	umask(0022);
	close(STDIN_FILENO);
	int fd = open("/dev/null",O_RDWR);
	if(fd == -1)sys_err("open error");
	dup2(fd,STDOUT_FILENO);
	dup2(fd,STDERR_FILENO);
	while(1);
	return 0;
}
