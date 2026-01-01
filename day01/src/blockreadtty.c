#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char * argv[])
{
	char buf[10];
	int n;
	n = read(STDIN_FILENO, buf,10);
	if(n<0)
	{
		perror("Read error!\n");
		exit(1);
	}
	write(STDOUT_FILENO,buf,n);
	return 0;
}
