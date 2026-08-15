#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<errno.h>

#define MAX_BUFFER_SIZE 1024

#define TRUE 0
#define FALSE 1 

typedef int BOOL;

void searchInvertedPattern(char * str,char * str2,BOOL ignoreCase) 
{
    char * temp = NULL;
    char * addr = NULL;
    BOOL bret = FALSE;    
    
    while(*str != '\0')
    {
        addr = str;
        temp = str2;

        while((*str != '\n')&&(*str != '\0')) 
        {

            if(ignoreCase == TRUE)
            {
                if(((*temp >= 'A')&&(*temp <= 'Z'))&&((*str >= 'a')&&(*str <= 'z')))
                {
                    *temp = *temp + 32;
                }
                else if(((*temp >= 'a')&&(*temp <= 'z'))&&((*str >= 'A')&&(*str <= 'Z')))
                {
                    *temp = *temp - 32;
                }
            }

            while((*temp != '\0') && (*temp == *str))
            {   
                str++;
                temp++;

                if(ignoreCase == TRUE)
                {
                    // printf("Inside Ignore Case conidtion: %d\n",ignoreCase);
                    if(((*temp >= 'A')&&(*temp <= 'Z'))&&((*str >= 'a')&&(*str <= 'z')))
                    {
                        *temp = *temp + 32;
                    }
                    else if(((*temp >= 'a')&&(*temp <= 'z'))&&((*str >= 'A')&&(*str <= 'Z')))
                    {
                        *temp = *temp - 32;
                    }
                }
            }

            if(*temp == '\0')
            {
                bret = TRUE;
            }
            else 
            {
                bret = FALSE;
                temp = str2;
            }
        
            str++;
        }   
        
        if(bret == FALSE)
        {
            while((*addr != '\n')&&(*addr != '\0'))
            {
                printf("%c",*addr);
                addr++;
            }
            printf("\n");
        }

        addr = NULL;
        bret = FALSE;
        temp = NULL;
        str++;
    }

    addr = NULL;
    temp = NULL;
    str = NULL;
    str2 = NULL;
}

void searchPattern(char * str,char * str2,BOOL ignoreCase)
{
    char * temp = NULL;
    char * addr = NULL;
    BOOL bret = FALSE;    
    
    // printf("ignore Case Value: %d",ignoreCase);
    while(*str != '\0')
    {
        addr = str;
        temp = str2;

        while((*str != '\n')&&(*str != '\0')) 
        {
            if(ignoreCase == TRUE)
            {
                // printf("Inside Ignore Case conidtion: %d\n",ignoreCase);
                if(((*temp >= 'A')&&(*temp <= 'Z'))&&((*str >= 'a')&&(*str <= 'z')))
                {
                    *temp = *temp + 32;
                }
                else if(((*temp >= 'a')&&(*temp <= 'z'))&&((*str >= 'A')&&(*str <= 'Z')))
                {
                    *temp = *temp - 32;
                }
            }

            while((*temp != '\0') && (*temp == *str))
            {
                // printf("Inside While LOOP Value of Temp: %c\n",*temp);
                // printf("Inside While LOOP Value of Str: %c\n",*str);   
                
                str++;
                temp++;

                if(ignoreCase == TRUE)
                {
                    // printf("Inside Ignore Case conidtion: %d\n",ignoreCase);
                    if(((*temp >= 'A')&&(*temp <= 'Z'))&&((*str >= 'a')&&(*str <= 'z')))
                    {
                        *temp = *temp + 32;
                    }
                    else if(((*temp >= 'a')&&(*temp <= 'z'))&&((*str >= 'A')&&(*str <= 'Z')))
                    {
                        *temp = *temp - 32;
                    }
                }
            }

            if(*temp == '\0')
            {
                bret = TRUE;
            }
            else 
            {
                bret = FALSE;
                temp = str2;
            }
        
            str++;
        }   
        
        if(bret == TRUE)
        {
            while((*addr != '\n')&&(*addr != '\0'))
            {
                printf("%c",*addr);
                addr++;
            }
            printf("\n");
        }

        addr = NULL;
        bret = FALSE;
        temp = NULL;
        str++;
    }

    addr = NULL;
    temp = NULL;
    str = NULL;
    str2 = NULL;
}

int countMatchedPattern(char * str,char * str2,BOOL ignoreCase)
{
    char * temp = NULL;
    int icnt = 0;
    BOOL bret = FALSE;

    while(*str != '\0')
    {
        temp = str2;

        while((*str != '\n')&&(*str != '\0'))  
        {
            if(ignoreCase == TRUE)
            {
                if(((*temp >= 'A')&&(*temp <= 'Z'))&&((*str >= 'a')&&(*str <= 'z')))
                {
                    *temp = *temp + 32;
                }
                else if(((*temp >= 'a')&&(*temp <= 'z'))&&((*str >= 'A')&&(*str <= 'Z')))
                {
                    *temp = *temp - 32;
                }
            }

            while((*temp != '\0') && (*temp == *str))
            {   
                str++;
                temp++;

                if(ignoreCase == TRUE)
                {
                    // printf("Inside Ignore Case conidtion: %d\n",ignoreCase);
                    if(((*temp >= 'A')&&(*temp <= 'Z'))&&((*str >= 'a')&&(*str <= 'z')))
                    {
                        *temp = *temp + 32;
                    }
                    else if(((*temp >= 'a')&&(*temp <= 'z'))&&((*str >= 'A')&&(*str <= 'Z')))
                    {
                        *temp = *temp - 32;
                    }
                }
            }

            if(*temp == '\0')   
            {
                bret = TRUE;
            }
            else 
            {
                bret = FALSE;
                temp = str2;
            }   

            str++;
        }   

        if(bret == TRUE)
        {
            icnt++;
        }
        
        bret = FALSE;
        temp = NULL;
        str++;
    }

    temp = NULL;
    str = NULL;
    str2 = NULL;

    return icnt;
}

int countInvertedPattern(char * str,char * str2,BOOL ignoreCase)
{
    char * temp = NULL;
    int icnt = 0;
    BOOL bret = FALSE;

    while(*str != '\0')
    {
        temp = str2;

        while((*str != '\n')&&(*str != '\0'))  
        {
            if(ignoreCase == TRUE)
            {
                if(((*temp >= 'A')&&(*temp <= 'Z'))&&((*str >= 'a')&&(*str <= 'z')))
                {
                    *temp = *temp + 32;
                }
                else if(((*temp >= 'a')&&(*temp <= 'z'))&&((*str >= 'A')&&(*str <= 'Z')))
                {
                    *temp = *temp - 32;
                }
            }

            while((*temp != '\0') && (*temp == *str))
            {   
                str++;
                temp++;

                if(ignoreCase == TRUE)
                {
                    // printf("Inside Ignore Case conidtion: %d\n",ignoreCase);
                    if(((*temp >= 'A')&&(*temp <= 'Z'))&&((*str >= 'a')&&(*str <= 'z')))
                    {
                        *temp = *temp + 32;
                    }
                    else if(((*temp >= 'a')&&(*temp <= 'z'))&&((*str >= 'A')&&(*str <= 'Z')))
                    {
                        *temp = *temp - 32;
                    }
                }
            }

            if(*temp == '\0')   
            {
                bret = TRUE;
            }
            else 
            {
                bret = FALSE;
                temp = str2;
            }   

            str++;
        }   

        if(bret == FALSE)
        {
            icnt++;
        }
        
        bret = FALSE;
        temp = NULL;
        str++;
    }

    temp = NULL;
    str = NULL;
    str2 = NULL;

    return icnt;
}

void grepSingleFile(char * fileName,char * pattern,char * option)
{
    int fd = 0;
    static int icnt = 0;
    BOOL ignoreCase = FALSE;
    int iRet = 0;
    char Buffer[MAX_BUFFER_SIZE];

    memset(Buffer,'\0',MAX_BUFFER_SIZE);

    // printf("File Name is: %s\n",fileName);
    // printf("Pattern to Search is: %s\n",pattern);
    
    fd = open(fileName,O_RDONLY);

    if(fd == -1)
    {
        printf("Error Occured while Opening File\n");
        perror("");

        return;
    }

    if((strcmp("-c",option) == 0) || (strcmp("-rc",option) == 0))
    {
        while((iRet = read(fd,Buffer,MAX_BUFFER_SIZE)) != 0)
        {
            icnt += countMatchedPattern(Buffer,pattern,ignoreCase);
            // printf("After Search Pattern: %s\n",pattern);
            memset(Buffer,'\0',MAX_BUFFER_SIZE);
        }
        
        printf("%d\n",icnt);
    }
    else if((strcmp("-v",option) == 0) || (strcmp("-rv",option) == 0))
    {
        while((iRet = read(fd,Buffer,MAX_BUFFER_SIZE)) != 0)
        {
            searchInvertedPattern(Buffer,pattern,ignoreCase);
            // printf("After Search Pattern: %s\n",pattern);
            memset(Buffer,'\0',MAX_BUFFER_SIZE);
        }
    }
    else if((strcmp("-i",option) == 0) || (strcmp("-ri",option) == 0))
    {
        ignoreCase = TRUE;

        while((iRet = read(fd,Buffer,MAX_BUFFER_SIZE)) != 0)
        {
            searchPattern(Buffer,pattern,ignoreCase);
            // printf("After Search Pattern: %s\n",pattern);
            memset(Buffer,'\0',MAX_BUFFER_SIZE);
        }
    }
    else if((strcmp("-ci",option) == 0) || (strcmp("-rci",option) == 0))
    {
        ignoreCase = TRUE;

        while((iRet = read(fd,Buffer,MAX_BUFFER_SIZE)) != 0)
        {
            icnt += countMatchedPattern(Buffer,pattern,ignoreCase);
            // printf("After Search Pattern: %s\n",pattern);
            memset(Buffer,'\0',MAX_BUFFER_SIZE);
        }
        
        printf("%d\n",icnt);
    }
    else if((strcmp("-vi",option) == 0) || (strcmp("-rvi",option) == 0))
    {
        ignoreCase = TRUE;

        while((iRet = read(fd,Buffer,MAX_BUFFER_SIZE)) != 0)
        {
            searchInvertedPattern(Buffer,pattern,ignoreCase);
            // printf("After Search Pattern: %s\n",pattern);
            memset(Buffer,'\0',MAX_BUFFER_SIZE);
        }
    }
    else if((strcmp("-cv",option) == 0) || (strcmp("-rcv",option) == 0))
    {
        while((iRet = read(fd,Buffer,MAX_BUFFER_SIZE)) != 0)
        {
            icnt += countInvertedPattern(Buffer,pattern,ignoreCase);
            // printf("After Search Pattern: %s\n",pattern);
            memset(Buffer,'\0',MAX_BUFFER_SIZE);
        }
        
        printf("%d\n",icnt);
    }
    else if((strcmp("-cvi",option) == 0) || (strcmp("-rcvi",option) == 0))
    {
        ignoreCase = TRUE;

        while((iRet = read(fd,Buffer,MAX_BUFFER_SIZE)) != 0)
        {
            icnt += countInvertedPattern(Buffer,pattern,ignoreCase);
            // printf("After Search Pattern: %s\n",pattern);
            memset(Buffer,'\0',MAX_BUFFER_SIZE);
        }
        
        printf("%d\n",icnt);
    }
    else 
    {
        while((iRet = read(fd,Buffer,MAX_BUFFER_SIZE)) != 0)
        {
            searchPattern(Buffer,pattern,ignoreCase);
            // printf("After Search Pattern: %s\n",pattern);
            memset(Buffer,'\0',MAX_BUFFER_SIZE);
        }
    }

    icnt = 0;
    close(fd);
    fileName = NULL;
    pattern = NULL;

    // return;
}

void grepRecursive(char * pattern,char * option) 
{
    DIR * dp = NULL;
    struct dirent * dobj;
    char * temp = pattern;

    dp = opendir(".");

    if(dp == NULL)
    {
        printf("Unable to access directory\n");
        perror("");
    }

    errno = 0;

    if(strcmp("-rc",option) == 0)
    {
        while((dobj = readdir(dp)) != NULL)
        {
            if(access(dobj->d_name,X_OK) != 0)
            {
                printf("%s: ",dobj->d_name);
                grepSingleFile(dobj->d_name,temp,"-c");
                printf("\n");
            }
        }
    }
    else if(strcmp("-rcv",option) == 0)
    {
        while((dobj = readdir(dp)) != NULL)
        {
            if(access(dobj->d_name,X_OK) != 0)
            {
                printf("%s: ",dobj->d_name);
                grepSingleFile(dobj->d_name,temp,"-cv");
                printf("\n");
            }
        }
    }
    else if(strcmp("-rv",option) == 0)
    {
        while((dobj = readdir(dp)) != NULL)
        {
            if(access(dobj->d_name,X_OK) != 0)
            {
                printf("%s: ",dobj->d_name);
                grepSingleFile(dobj->d_name,temp,"-v");
                printf("\n");
            }
        }
    }
    else if(strcmp("-ri",option) == 0)
    {
        while((dobj = readdir(dp)) != NULL)
        {
            if(access(dobj->d_name,X_OK) != 0)
            {
                printf("%s: ",dobj->d_name);
                grepSingleFile(dobj->d_name,temp,"-i");
                printf("\n");
            }
        }
        
    }
    else if(strcmp("-rvi",option) == 0)
    {
        while((dobj = readdir(dp)) != NULL)
        {
            if(access(dobj->d_name,X_OK) != 0)
            {
                printf("%s: ",dobj->d_name);
                grepSingleFile(dobj->d_name,temp,"-vi");
                printf("\n");

            }
    
        }
        
    }
    else if(strcmp("-rci",option) == 0)
    {
        while((dobj = readdir(dp)) != NULL)
        {
            if(access(dobj->d_name,X_OK) != 0)
            {
                printf("%s: ",dobj->d_name);
                grepSingleFile(dobj->d_name,temp,"-ci");
                printf("\n");

            }
        }
    }
    else if(strcmp("-rcvi",option) == 0)
    {
        while((dobj = readdir(dp)) != NULL)
        {
            if(access(dobj->d_name,X_OK) != 0)
            {
                printf("%s: ",dobj->d_name);
                grepSingleFile(dobj->d_name,temp,"-cvi");
                printf("\n");

            }
        }
    }
    else 
    {
        while((dobj = readdir(dp)) != NULL)
        {
            // if()c
            if(access(dobj->d_name,X_OK) != 0)
            {
                printf("%s: ",dobj->d_name);
                grepSingleFile(dobj->d_name,temp,"");

                printf("\n");

            }
        }
    }

    closedir(dp);
    pattern = NULL;
}


int main(int argc,char * argv[])
{

    // printf("Jay Ganesh...\n");

    if((argc < 2) || (argc > 5))
    {
        printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
        printf("Type 'grep --help' for more information\n");
        return 1;
    }

    if((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1],"--help") == 0))
    {
        printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n\
        Search for PATTERNS in each FILE.\n\n\
        Example1: grepx -i 'hello world' menu.h main.c\n\n\
        Example2: grepx -rcvi\n\n\
        PATTERNS can contain multiple patterns separated by newlines.\n\
        Pattern selection and interpretation:\n\
        Usage: grep [OPTION]... PATTERNS [FILE]...\n\
        Search for PATTERNS in each FILE.\n\
        Example: grep -i 'hello world' menu.h main.c\n\n\
        PATTERNS can contain multiple patterns separated by newlines.\n\
        Pattern selection and interpretation:\n\
        -r = recursive\n\
             Read  all  files  under  each  directory, recursively, following symbolic links only if they are on the command\n\
             line.  Note that if no file operand is given, grep searches the working directory.  This is equivalent  to  the\n\
             -d recurse option.\n\
        -c = count\n\
             Suppress  normal  output;  instead  print  a  count  of  matching  lines  for  each  input  file.  With the -v,\n\
             --invert-match option (see above), count non-matching lines.\n\
        -v = invert-match\n\
             Invert the sense of matching, to select non-matching lines.\n\
        -i = ignore-case\n\
             Ignore  case  distinctions  in  patterns and input data, so that characters that differ only in case match each\n\
             other.\n");
        
        return -1;
    }

    if(argc > 3)
    {                                                // argv[0] argv[1]  argv[2] argv[3]
        grepSingleFile(argv[3],argv[2],argv[1]);    // ./grepx  [option] Pattern FileName
    }
    else 
    {
        if((strcmp(argv[1],"-r") == 0) || (strcmp(argv[1],"-rc") == 0) || 
        (strcmp(argv[1],"-rv") == 0) || (strcmp(argv[1],"-ri") == 0) || 
        (strcmp(argv[1],"-rcv") == 0) || (strcmp(argv[1],"-rci") == 0) || 
        (strcmp(argv[1],"-rvi") == 0) || (strcmp(argv[1],"-rcvi") == 0))
        {                                     // argv[0] argv[1]   argv[2]
            grepRecursive(argv[2],argv[1]);  // ./grepx  [option]  Pattern
        }
        else 
        {
            grepSingleFile(argv[2],argv[1],"");    // ./grepx Pattern FileName
        }
    }

    return 0;
}