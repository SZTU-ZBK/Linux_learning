#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char * argv[])
{
	int ret;
	struct stat sbuf;
	ret = stat (argv[0],&sbuf);
	if(ret == -1)
	{
		perror("stat error\n");
		exit(0);
	}
	printf("st_size:%ld\n",sbuf.st_size);
	return 0;
}
