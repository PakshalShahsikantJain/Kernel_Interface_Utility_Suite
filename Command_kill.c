/*
    Author: Pakshal Shashikant Jain
    Date: 15/08/2026
    Program: Implementation of kill Command
*/

//Required Header Files 
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>

/*
    Function: sendSignalToProcess
    parameter: argc (No of arguments) arguments
    Return Value: Void
*/
void sendSignalToProcess(int argc,char * argv[]) 
{
    int pid = 0;
    int iRet = 0;
    int i = 0;
    int signal = 0;
    char error[500] = {'\0'};

    if((argv[1][0] == '-') && (!((argv[1][1] >= 'a') && (argv[1][1] <= 'z'))))
    {

        signal = atoi(argv[1] + 1);
    
        for(i = 2;i <= argc - 1;i++)
        {
            iRet = kill(atoi(argv[i]),signal);
            
            if(iRet == -1)
            {
                snprintf(error,sizeof(error),"Kill: (%d) - ",atoi(argv[i]));
                perror(error);
            }
        }
    }
    else if((strcmp("-s",argv[1]) == 0) || (strcmp("--signal",argv[1]) == 0))
    {
        signal = atoi(argv[2]);
        
        if(!argv[3])
        {
            printf("Insufficient number of arguments passed: \n");
            printf("Type --usage or --help for more details\n");
            return;
        }

        pid = atoi(argv[3]);

        for(i = 3;i <= argc - 1;i++)
        {
            iRet = kill(atoi(argv[i]),signal);
            
            if(iRet == -1)
            {
                snprintf(error,sizeof(error),"Kill: (%d) - ",atoi(argv[i]));
                perror(error);
            }
        }
    }
    else
    {
        for(i = 1;i <= argc - 1;i++)
        {
            iRet = kill(atoi(argv[i]),SIGKILL);
            
            if(iRet == -1)
            {
                snprintf(error,sizeof(error),"Kill: (%d) - ",atoi(argv[i]));
                perror(error);
            }
        } 
    }
}

//Entry point Function 
int main(int argc,char * argv[])
{
    int iRet = 0;
    int pid = 0;

    printf("Jay Ganesh....\n");

    if(argc == 1)
    {   
        printf("Insufficient arguments passed\n");
        printf("Type --help or --usage for more Details\n");
        
        return 1;
    }

    if(argc == 2)
    {
        if((strcmp(argv[1],"-u") == 0) || (strcmp(argv[1],"--usage") == 0))
        {
            printf("%s [options] <pid> [...]\n",argv[0]);
        }
        else if((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1],"--help") == 0))
        {
            printf("killx - send a signal to a process\n");
            printf("\tThe  default  signal  for  kill is TERM.  Use -l or -L to list available signals.  Particularly useful signals include HUP, INT, KILL,\
            STOP, CONT, and 0.  Alternate signals may be specified in three ways: -9, -SIGKILL or -KILL.  Negative  PID  values  may  be  used  to\
            choose  whole process groups; see the PGID column in ps command output.  A PID of -1 is special; it indicates all processes except the\
            kill process itself and init.\n");
            printf("<pid> [...]\n\tSend signal to every <pid> listed.\n");
            printf("-<signal>\n-s <signal>\n--signal <signal>\n\tSpecify the signal to be sent.  The signal can be specified by using name or number.\n");
            printf("-l, --list [signal]\n\tList signal names.  This option has optional argument, which will convert signal number to signal name, or other way round.\n");
            printf("-L, --table\n\tList signal names in a nice table.\n");

            printf("\n Example: killx -9 pid\n");
        }
        else 
        {

            printf("%s\n",argv[1]);

            pid = atoi(argv[1]);

            iRet = kill(pid,SIGKILL);
            
            if(iRet == -1)
            {
                perror("Kill: Error");
                return -1;
            }
        }
    }
    else 
    {
        sendSignalToProcess(argc,argv); //Call to user defined function 
    }

    return 0;
}