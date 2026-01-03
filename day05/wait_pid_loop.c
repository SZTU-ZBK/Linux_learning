#include <stdio.h>
#include <unistd.h>
int main(int argc,char * argv[])
{
	pid_t pid,wpid;
	int i=0;
	for(i = 0;i < 5;++i)
	{
		pid = fork();
		if(pid == 0)
		{
			printf("I'm child process,my pid is %ld!\n",getpid());
			break;
		}
	}
	for(int j = 0;j < 5;++j)
	{
		wpid = waitpid(0,NULL,0);
		if(wpid == -1)perror("waitpid error!");
		else printf("The %ld child process was recycled!\n",wpid);
	}
	return 0;
}
