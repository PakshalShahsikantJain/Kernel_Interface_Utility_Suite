#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>

//	./rmx FileName
//	argv[0]		argv[1]
//	argc = 2	argc = 2

int main(int argc,char * argv[])
{
	if(argc != 2)
	{
		printf("Error: Insuffient arguments\n");
		printf("Use as : ./rmx path\n");
		
		return -1;
	}

	int iRet = 0;

	iRet = unlink(argv[1]);

	if(iRet == -1)
	{
		printf("Error : Unable to delete\n");
		return -1;
	}

	return 0;
}
