#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

//	./cdx 		directoryPath
//	argv[0] 	argv[1]		
//	argc = 2

/*
	Accpet New Directory Path 
	Call chdir with that path
	Call getcwd to check the changed path
*/

int main(int argc,char * argv[])
{
	if(argc != 2)
	{
		printf("Error: Insuffient arguments\n");
		printf("Use as : ./cdx DirectoryPath\n");
		
		return -1;
	}

	if(chdir(argv[1]) == -1)
	{
		printf("Unable to change current directory\n");
		return -1;
	}

	char Buffer[256] = {'\0'};
	
	getcwd(Buffer,sizeof(Buffer) - 1);
	
	printf("Current Directory changed to %s\n",Buffer);


	return 0;
}
