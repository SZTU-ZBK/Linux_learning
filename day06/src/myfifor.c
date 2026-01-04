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
	if(ret == -1 && errno != EEXIST) sys_error("open_error!");
	char buf[20];
	for(int i = 0;i<1000;i++)
	{
		ret = read(fd,buf,sizeof(buf));
		if(ret == -1)sys_error("write_error");
		else write(STDOUT_FILENO,buf,ret);//这里不能用printf，因为buf里未必有‘/0’,只能读到多少往屏幕写多少
	}
	return 0;
}
