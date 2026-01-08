#include <stdio.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
	int time;
	time = alarm(1);
	int i = 0;
	while(1)
	{
		printf("time:%d,count:%d\n",time,i++);
	}
	return 0;
}
