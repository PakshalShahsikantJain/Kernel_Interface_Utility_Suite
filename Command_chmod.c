#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>

int main(int argc,char * argv[])
{
    mode_t mode = 0;
    int iRet = 0;

    if(argc == 2)
    {
        if((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1],"--help") == 0))
        {
            printf("Usage: chmod MODE[,MODE]... FILE...\n"
            "Change the mode of each FILE to MODE\n");
            
            return 0;
        }
    }

    if(argc < 2)
    {
        printf("chmod: missing operand\n"
               "Try 'chmodx --help' for more information.\n");
        
        return 1;
    }

    if(argc < 3)
    {
        printf("chmod: missing operand after %s\n",argv[1]);
        printf("Try 'chmodx --help' for more information.\n");  
        return 1;
    }

    mode = atoi(argv[2]);

    if(mode == 777)
    {
        mode = 0777;
    }

    iRet = chmod(argv[1],mode);

    if(iRet == -1)
    {
        perror("Error Occured:");
        return -1;
    }

    printf("Permissions Changed Successfully\n");

    return 0;
}