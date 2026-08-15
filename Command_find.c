///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  
//  Author  :   Pakshal Shashikant Jain
//  Date    :   14/08/2026 
//  Program :   To Find File in Entered Directory
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Required Libraries
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include<limits.h>

/*
    Function: displayAllFiles
    parameter: pathToSearch (directory)
    Description: To Display All Files of Entered Directory 
    Return Value: Nothing
*/
void displayAllFiles(char * pathToSearch)
{
    DIR * dp = NULL;
    struct stat sobj;
    struct dirent * dstr = NULL;
    static int depth = 0;
    int i = 0;
    char abs_path[PATH_MAX];
    char sret[300] = {'\0'};

    // printf("Path to Search: %ld\n",strlen(pathToSearch));

    dp = opendir(pathToSearch);

    if(dp == NULL)
    {
        printf("%d",errno);

        printf("Error Occure while opening directory\n");
        perror("");
        return;
    }

    while((dstr = readdir(dp)) != NULL)
    {
        if((strcmp(".",dstr->d_name) == 0) || (strcmp(dstr->d_name,"..") == 0))
        {
            continue;
        }

        if(depth != 0)
        {
            for(i = 0;i < depth;i++)
            {
                printf("\t");
            }
        }

        if(dstr->d_type == DT_DIR)
        {
            printf("%s/ \n",dstr->d_name);
            
            snprintf(sret,sizeof(sret),"%s/%s",pathToSearch,dstr->d_name);

            // printf("%s\n",sret);
            if (realpath(sret, abs_path) != NULL) 
            {
                // printf("The absolute path is: %s\n", abs_path);
                depth++;
                displayAllFiles(abs_path);
                depth--;
            } 
            else 
            {
                perror("Error");
                return;
            }
        }
        else
        {
            printf("%s\n",dstr->d_name);
        }
    }

    closedir(dp);

    return;
}

/*
    Function:searchFile
    Paramter: pathToSearch, fileName
    Desciption: Function To Search File
    Return Value: Nothing
*/
void searchFile(char * pathToSearch,char * fileName)
{
    DIR * dp = NULL;
    struct stat sobj;
    struct dirent * dstr = NULL;
    static int depth = 0;
    int i = 0;
    char abs_path[PATH_MAX];
    char sret[300] = {'\0'};
    
    dp = opendir(pathToSearch);

    if(dp == NULL)
    {
        printf("%d",errno);

        printf("Error Occure while opening directory\n");
        perror("");
        return;
    }

    while((dstr = readdir(dp)) != NULL)
    {
        if((strcmp(".",dstr->d_name) == 0) || (strcmp(dstr->d_name,"..") == 0))
        {
            continue;
        }

        if(dstr->d_type == DT_DIR)
        {
            if(strcmp(fileName,dstr->d_name) == 0)
            {
                printf("%s/%s \n",pathToSearch,dstr->d_name);
            }
            
            snprintf(sret,sizeof(sret),"%s/%s",pathToSearch,dstr->d_name);

            if (realpath(sret, abs_path) != NULL) 
            {
                searchFile(abs_path,fileName);
            } 
            else 
            {
                perror("Error");
                return;
            }
        }
        else
        {
            if(strcmp(fileName,dstr->d_name) == 0)
            {
                printf("%s/%s\n",pathToSearch,dstr->d_name);
            }
        }
    }

    closedir(dp);

    return;
}

//Entry Point Function 
int main(int argc,char * argv[])
{
    char * path = NULL; 
    char * fileName = NULL;
    char * flag = NULL;

    printf("Jay Ganesh....\n");

    if((argc == 2) && ((strcmp(argv[1],"-u") == 0)||(strcmp(argv[1],"--usage") == 0)))
    {
        printf("Usage : find /\n");
        printf("Example: find /etc -name passwd");
        return 0;
    }

    if(argc < 2)
    {
        path = ".";
        displayAllFiles(path);
    }
    else if(argc == 2)
    {
        path = argv[1];
        displayAllFiles(path);
    }
    else if(argc == 3)   //./findx -name passwd 
    {

        if(strcmp(argv[1],"-name") == 0)
        {
            path = ".";
            fileName = argv[2];
            searchFile(path,fileName);
        }
        else
        {
            path = argv[1];
            fileName = argv[2];
            searchFile(path,fileName);            
        }

    }
    else if(argc == 4) // ./findx /etc -name passwd
    {
        path = argv[1];
        flag = argv[2];
        fileName = argv[3];

        if(strcmp(flag,"-name") == 0)
        {
            searchFile(path,fileName);
        }
    }

    return 0;
}