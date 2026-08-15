#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main(int argc,char * argv[])
{
    int iRet = 0;

    if(argc < 2 || argc > 5)
    {
        printf("Invalid number of arguments entered\n");
        printf("Try './lnx --help / -h' for more information\n");
        return -1;
    }

    if(argc == 2)
    {
        if((strcmp(argv[1],"-h") == 0)||(strcmp(argv[1],"--help") == 0))
        {
            printf("Usage: lnx [OPTION]... [-T] TARGET LINK_NAME\n");

            printf("\nCreate a link to TARGET with the name LINK_NAME.\n"
                    "By default, each destination (name of new link) should not already exist.\n"
                    "When creating hard links, each TARGET must exist.  Symbolic links\n"
                    "can hold arbitrary text; if later resolved, a relative link is\n"
                    "interpreted in relation to its parent directory.\n");
            
            printf("\nOptions: \n");
            printf("-f, --force                 remove existing destination files\n");
            printf("-s, --symbolic              make symbolic links instead of hard links\n");
        } 
        else 
        {
            printf("Invalid Option Entered\n");
            printf("Try ./lnx --help for more information\n");
            return -1;
        }

        return 0;
    }

    if(argc == 3)
    {
        if((strcmp(argv[1],"-s") == 0) || (strcmp(argv[1],"-f") == 0))
        {
            printf("lnx: missing file operand\n"
                    "Try './lnx --help' for more information.\n");

            return -1;
        }

        iRet = link(argv[1],argv[2]);

        if(iRet == -1)
        {
            perror("Error Occured: ");
            return -1;
        }

        printf("Hard Link Created Successfully\n");
    }
    else if(argc == 4)
    {
        if(strcmp(argv[1],"-s") == 0)
        {
            iRet = symlink(argv[2],argv[3]);

            if(iRet == -1)
            {
                perror("");
                return -1;
            }

            printf("Symbolic (Soft) Link Created Successfully\n");
        }
        else if(strcmp(argv[1],"-f") == 0)
        {
            iRet = link(argv[2],argv[3]);

            if(iRet == -1)
            {
                if(errno == EEXIST)
                {
                    iRet = unlink(argv[3]);

                    if(iRet == -1)
                    {
                        perror("Error unlink: ");
                        return -1;
                    }

                    iRet = link(argv[2],argv[3]);

                    if(iRet == -1)
                    {
                        perror("Error link: ");
                        return -1;
                    }

                    printf("Hard Link Created Successfully\n");
                    return 0;
                }
                else 
                {
                    perror("Error link: ");
                    return -1;
                }
            }
            
            printf("Hard Link Created Successfully\n");
        }
        else 
        {
            printf("Invalid argument Entered\n");
            printf("Try lnx --help for more information\n");
        }
    }
    else if(argc == 5)
    {
        if((strcmp(argv[1],"-s") == 0) && (strcmp(argv[2],"-f") == 0))
        {
            iRet = symlink(argv[3],argv[4]);

            if(iRet == -1)
            {
                if(errno == EEXIST)
                {
                    iRet = unlink(argv[4]);

                    if(iRet == -1)
                    {
                        perror("Error unlink: ");
                        return -1;
                    }

                    iRet = symlink(argv[3],argv[4]);

                    if(iRet == -1)
                    {
                        perror("Error symlink: ");
                        return -1;
                    }

                    printf("Symbolic (Soft) Link Created Successfully\n");
                    return 0;
                }
                else 
                {
                    perror("Error symlink: ");
                    return -1;
                }
            }

            printf("Symbolic (Soft) Link Created Successfully\n");
        }
        else 
        {
            printf("Invalid arguments Entered\n");
            printf("Try lnx --help for more information\n");
        }
    }

    return 0;
}