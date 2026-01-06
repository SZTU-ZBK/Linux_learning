#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
void sys_error(char * str)
{
	perror(str);
	exit(1);
}
int var = 100;
struct student{
	int ID;
	char name[10];
};
int main(int argc,char *argv[])
{
	struct student stu = {1,"ZBK"};
	int fd;
	struct student *p;
	fd = open("testmmap",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd == -1) sys_error("open error!");
	ftruncate(fd,sizeof(stu));
	p = (struct student *)mmap(NULL,sizeof(stu),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);	
	if(p == MAP_FAILED)
	{
		sys_error("mmap error!");
	}
	close(fd);
	while(1)
	{
		memcpy(p,&stu,sizeof(stu));
		sleep(1);
		stu.ID++;
	}
	return 0;
}

