#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
bool Is_dir(const char * path)
{
	struct stat info;
	if(stat(path,&info) != 0)
	{
		perror("stat error!\n");
		return false;
	}
	if(S_ISDIR(info.st_mode))
	{
		return true;
	}
	return 0;
}
void myls_R(const char * path)
{
	DIR * dp;
	struct dirent * sdp;
	dp = opendir(path);
        if(dp == NULL)
        {
		printf("%s\n",path);
                perror("opendir error!\n");
                exit(1);
        }
	char tmp_path[256];
        while((sdp=readdir(dp)) != NULL)
        {
                if(!strcmp(sdp->d_name, ".") || !strcmp(sdp->d_name, "..")) continue;
                sprintf(tmp_path,"%s/%s",path, sdp->d_name);
                printf("%s\n",tmp_path);
		if(Is_dir(tmp_path))myls_R(tmp_path);
        }
        closedir(dp);
}

int main(int argc,char * argv[])
{
        char real_path[256];
	for(int i = 1;i<argc;++i)
	{
		sprintf(real_path,"%s",argv[i]);
        	size_t length = strlen(real_path);
        	if(real_path[length-1] == '/')
        	{
                	real_path[length-1]='\0';
        	}	
		myls_R(real_path);
	}
	return 0;
}

