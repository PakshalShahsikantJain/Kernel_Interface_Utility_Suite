///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author: Pakshal Shashikant Jain
//	Date: 20/02/2026
//	Program: Implementation of ps Command to Display List of Current Running Process
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include<errno.h>

typedef int BOOL;

#define TRUE 1
#define FALSE 0

//	./psx 
//	argv[0]		
//	argc = 1

/*
	open the directory /proc
	openall subdirectory while name is integer
	Inside that directory open comm file
	Display the name inside that file
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function name: Directory Name
//	Description: Function to check directory name is of type integer
//	Return Type: BOOLEAN
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL isInteger(char * dirName) 
{
	//Loop To check Directory name is of type integer
	while(*dirName != '\0')
	{
		if((*dirName >= '0')&&(*dirName <= '9'))
		{
			dirName++;
		}
		else 
		{
			break;
		}
	}

	if((*dirName == '\0'))
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function name: openSubDirectory
//	Description: Function to open sub directory of parent direcrtory
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void openSubDirectory(char * dirName)
{
	DIR * dp = NULL;
	struct dirent * ptr = NULL;
	int fd = 0;
	char Buffer[1024] = {'\0'};
	char fileName[260] = {'\0'};
	int iRet = 0;
	
	/////////////////////////////////////////////////////////////////////////////////
	//
	//  System Call: opendir
	//	Description: To open directory specified
	//
	//////////////////////////////////////////////////////////////////////////////
	dp = opendir(dirName);

	if(dp == NULL)
	{
		perror("Error Occured while opening sub directory : ");
		printf("\n");
		return;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Loop to read directory file
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while((ptr = readdir(dp)) != NULL)
	{
		// printf("Subdirectory: %s\n",ptr->d_name);
		if(strcmp(ptr->d_name,"comm") == 0)
		{
			snprintf(fileName,sizeof(fileName),"%s/%s",dirName,ptr->d_name);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	//
	//	System call: open
	//	Description: To open file in read mode
	//
	////////////////////////////////////////////////////////////////////////////////
	fd = open(fileName,O_RDONLY);

	if(fd < 0)
	{
		perror("Error Occured while opening comm file: ");
		printf("\n");
		return;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// Loop to read whole file
	//////////////////////////////////////////////////////////////////////////////////////

	while((iRet = read(fd,Buffer,sizeof(Buffer))) != 0)     //read system call
	{
		printf("%s",Buffer);
	}

	if(errno)
	{
		perror("Error Occured while reading comm file: ");
		printf("\n");
		return;
	}

	close(fd);

}

//Entry Point Function with command line arguments
int main(int argc,char * argv[])
{
	DIR *dp = NULL;

	struct dirent *ptr = NULL;
	char dirName[20] = "/proc";

	//System call to open directory file
	dp = opendir(dirName);

	char fullpath[300];

	memset(fullpath,'\0',sizeof(fullpath));

	if(dp == NULL)
	{
		perror("operdir Error : ");
		printf("\n");
		return -1;
	}

	printf("PID\tCMD\t\n");
	
	//Loop To Read Directory File Opened
	while((ptr = readdir(dp)) != NULL)
	{
		if(isInteger(ptr->d_name) == TRUE)
		{
			printf("%s\t",ptr->d_name);
			snprintf(fullpath,sizeof(fullpath),"%s/%s",dirName,ptr->d_name);    // builing full path
			openSubDirectory(fullpath);   //call to user define function
		}
	}

	if(errno)
	{
		perror("readdir Error : ");
		printf("\n");
		return -1;
	}
	return 0;
}
