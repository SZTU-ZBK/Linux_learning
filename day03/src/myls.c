#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc , char * argv[])
{
	DIR * dp;
	struct dirent *sdp;
	dp = opendir(argv[1]);
	if(dp == NULL)
	{
		perror("opendir error!\n");
		exit(1);
	}
	while((sdp  =readdir(dp)) != NULL)
	{
		printf("%s\t",sdp->d_name);
	}
	printf("\n");
	closedir(dp);
	return 0;
}
