#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc ,char * argv[])
{
	pid_t pid,wpid;
	int i= 0;
	for(i = 0;i<5;++i)
	{
		sleep(1);
		pid = fork();
		if(pid == 0)
		{
			printf("I'm child processs,my pid is %d!\n",getpid());
			break;
		}
	}
	if(i==5)
	{
		for(int j=0;j<5;++j)
		{
			wpid = waitpid(0,NULL,0);
			if(wpid == -1) perror("waitpid error!");
			printf("child process %d was recycle!\n",wpid);
		}
	}
	return 0;
}

