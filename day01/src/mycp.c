#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include  <stdlib.h>
int main(int argc , char * arg[])	
{
	char buf[1024];
	int n = 0;
	int fd1 = open(arg[1],O_RDONLY);
	int fd2 = open(arg[2],O_RDWR|O_CREAT|O_TRUNC,0664);
	if(fd1 == -1 || fd2 == -1 )
	{
		perror("open error\n");
		exit(1);
	}
	while((n=read(fd1,buf,1024)) != 0 )
	{
		if(n<0)
		{
			perror("read error\n");
			break;
		}
		write(fd2,buf,n);
	}
	close(fd1);
	close(fd2);
	return 0;
}
