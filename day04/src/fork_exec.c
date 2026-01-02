#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc,char *argv[])
{
	printf("before fork 1~\n");
	printf("before fork 2~\n");
	printf("before fork 3~\n");
	pid_t pid;
	int fd;
	fd = open("./process_info.out",O_RDWR|O_CREAT,0644);
	pid = fork();
	if(pid == -1)
	{
		perror("fork error!");
		exit(1);
	}
	else if(pid == 0)
	{
		printf("child_process:---child is created!\n");
		int ret = dup2(fd,1);
		if(ret != -1)
		{
			execlp("ps","ps","aux",NULL);
			perror("exec error!");
			exit(1);
		}
		perror("duperror!");
	}
	sleep(1);

	printf("============end of file\n");
	return 0;
}

