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
	fd = open("testmmap",O_RDONLY,0644);
	if(fd == -1) sys_error("open error!");
	p = (struct student *)mmap(NULL,sizeof(stu),PROT_READ,MAP_SHARED,fd,0);
	if(p == MAP_FAILED)
	{
		sys_error("mmap error!");
	}
	close(fd);
	while(1)
	{
		printf("Student ID:%d,name:%s\n",p->ID,p->name);
		sleep(1);
	}
	return 0;
}

