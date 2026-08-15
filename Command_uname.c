#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>

//	./unamex 
//	argv[0]		
//	argc = 1

/*
	Call The System Call uname
	Print the information from utsname structure
*/

/*
struct utsname {
               char sysname[];    
               char nodename[];   
                                  
               char release[];    
                                   
               char version[];    
               char machine[];    
	           #ifdef _GNU_SOURCE
               char domainname[]; 
    	       #endif
           };
*/

int main(int argc,char * argv[])
{
	struct utsname obj;
	int iRet = 0;

	iRet = uname(&obj);

	if(iRet == -1)
	{
		printf("Error : Unable to fetch system information\n");

		return -1;
	}

	printf("Operating System name : %s\n",obj.sysname);
	printf("Node Name : %s\n",obj.nodename);
	printf("Opearting System version : %s\n",obj.release);

	return 0;
}
