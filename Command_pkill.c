/*
    Author: Pakshal Shashikant Jain 
    Date: 17/08/2026
    Program: Implementation of Command pkill - Kill Process By Name
*/

//Required Libraries
#include<stdio.h>
#include<fcntl.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

typedef int BOOL;

//User Defined MACROS

#define TRUE 0       
#define FALSE 1       

#define MAX_BUFFER_SIZE 1024

//Helper Functions
BOOL isDirNameInteger(char * dirName) 
{
    char * temp = dirName;

    while(*temp != '\0')
    {
        // if(((*temp >= 'A')&&(*temp <= 'Z'))||((*temp >= 'a')&&(*temp <= 'z')))
        // {
        //     break;
        // }   

        if(!((*temp >= '0')&&(*temp <= '9')))
        {
            break;
        }   

        temp++;
    }

    if(*temp == '\0')
    {
        return TRUE;
    }
    else 
    {
        return FALSE;
    }

    temp = NULL;
}

BOOL openAndReadFile(char * fileName,char * procName)
{
    int fd = 0;
    char Buffer[MAX_BUFFER_SIZE] = {'\0'};
    int iRet = 0;

    // printf("Filename is: %s\n",fileName);
    // printf("Proc name is: %s\n",procName);

    fd = open(fileName,O_RDONLY);

    if(fd == -1)
    {
        perror("open");
        return FALSE;
    }

    iRet = read(fd,Buffer,strlen(procName));

    if(iRet < 0)
    {
        perror("read");

        return FALSE;
    }

    close(fd);

    iRet = strcmp(Buffer,procName);

    // printf("Buffer is: %s %ld\n",Buffer,strlen(Buffer));
    // printf("Proc Name is: %s %ld\n",procName,strlen(Buffer));


    if(strcmp(Buffer,procName) == 0)
    {
        // printf("%s\n",Buffer);
        return TRUE;
    }
    else 
    {
        return FALSE;
    }
}

void killProcessByName(char * path,char * pattern,int signal) 
{
    int iRet = 0;
    DIR * dp = NULL;    
    struct dirent * dptr = NULL;
    BOOL bret = FALSE;
    char filepath[500] = {'\0'};
    int fd = 0;

    // printf("Path Entered is: %s\n",path);

    dp = opendir(path);

    if(dp == NULL)
    {
        perror("pkill:");
        return;
    }


    while((dptr = readdir(dp)) != NULL)
    {
        // printf("%s\n",dptr->d_name);

        if((dptr->d_type == DT_DIR) && ((bret = isDirNameInteger(dptr->d_name)) == TRUE))
        {   
            // printf("%s\n",dptr->d_name);

            snprintf(filepath,sizeof(filepath),"%s/%s/comm",path,dptr->d_name);

            bret = openAndReadFile(filepath,pattern);

            if(bret == TRUE)
            {
                iRet = kill(atoi(dptr->d_name),signal);

                if(iRet == -1)
                {
                    perror("kill");
                }

                printf("Killed Process: %s\n",dptr->d_name);
            }
        }
    }

    closedir(dp);
    dp = NULL;
    dptr = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Entry Point Function
int main(int argc,char * argv[])
{
    char path[MAX_BUFFER_SIZE] = {'\0'};
    char * processName = NULL;
    int Signal = 0;

    snprintf(path,sizeof(path),"/proc");

    printf("Jay Ganesh....\n");
    
    if(argc < 2)
    {
        printf("Invalid Number of arguments passed\n");
        printf("Type -h or --help for more details\n");
        
        return -1;
    }

    if(argc == 2)  // pkillx -h or pkillx chrome
    {
        if((strcmp(argv[1],"-h") == 0)||(strcmp(argv[1],"--help") == 0))
        {
            printf("Usage:\n");
            printf(" pkillx [options] <pattern>");
            printf("Options:\n");
            printf(" -<sig> signal to send (either number or name)\n");
            printf(" -e, --echo display what is killed\n");
            printf(" -c, --count count of matching processes\n");
            printf(" -f, --full use full process name to match\n");
            printf(" -h, --help display this help and exit\n");

            printf("Default behaviour is to Kill / Terminate the Process\n");

            printf("Example:\n");
            printf("\t pillx bash\n");
            return 0;
        }
        else 
        {
            killProcessByName(path,argv[1],SIGKILL);
        }
    }
    else  // pkillx -9 chrome
    {
        if(argv[1][0] == '-')
        {
            Signal = atoi(argv[1] + 1);

            killProcessByName(path,argv[2],Signal);
        }
    }


    return 0;
}