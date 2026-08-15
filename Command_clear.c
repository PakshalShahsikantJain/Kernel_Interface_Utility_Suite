/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 20/02/2026
//  Program: Implementation of Clear Command of Linux
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

//./clearx   -x
//argv[0]   argv[1](optional)

//argc = 2

//Entry Point function
int main(int argc,char * argv[])
{
    char ch[50] = {'\0'};

    if(argc > 1)
    {
        if((strcmp(argv[1],"-u") == 0) || (strcmp(argv[1],"-U") == 0))
        {
            printf("usage: ./clearx [options]\n");
            return 0;
        }
        else if((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1],"--help") == 0))
        {
            printf("OPTIONS: \n");
            printf("-x prevents clear from attempting to clear the scrollback buffer.\n");
            return 0;
        }
        else if(strcmp(argv[1],"-x") == 0)
        {
            strcpy(ch,"\033[2J\033[H");
        }
        else
        {
            printf("Invalid Option Entered\n");
            printf("For Help Type -h or --help\n");
            printf("For Help with usage Type -u or -U\n");
            return -1;
        }
    }
    else 
    {
        strcpy(ch,"\033c");
    }

    lseek(1,0,SEEK_SET);

    write(1,ch,sizeof(ch));

    lseek(1,0,SEEK_SET);

    return 0;
}