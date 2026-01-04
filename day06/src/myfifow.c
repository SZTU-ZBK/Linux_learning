#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
void sys_error(char *str)
{
	perror(str);
	exit(1);
}

int main(int argc ,char *argv[])
{

	int fd;
	int ret = mkfifo(argv[1],0644);
	if(ret == -1 && errno != EEXIST) sys_error("mkfifo_error!");
	fd = open(argv[1],O_RDWR|O_CREAT,0644);
	if(fd == -1) sys_error("open_error!");
	char string[50];
	for(int i = 0;i<1000;i++)
	{
		sprintf(string,"Hello world!%d\n",i);
		ret = write(fd,string,strlen(string));
		sleep(1);
		if(ret == -1)sys_error("write_error");
	}
	return 0;
}
