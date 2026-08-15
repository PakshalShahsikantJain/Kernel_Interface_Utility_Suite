#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<pwd.h>
#include<string.h>
#include<grp.h>

void displayIds(char * option1,char * option2,char * option3)
{
    gid_t * list = NULL;
    int size = 0;
    int iRet = 0;
    int i = 0;
    int uid = 0;
    int gid = 0;
    struct passwd * pwd = NULL;
    struct group * grp = NULL;
    long nggropus_max = 0;

    uid = geteuid();
    gid = getegid();

    pwd = getpwuid(uid);

    grp = getgrgid(gid);

    nggropus_max = sysconf(_SC_NGROUPS_MAX);

    list = (gid_t *)malloc(nggropus_max * sizeof(gid_t));

    iRet = getgroups(nggropus_max,list);

    if(iRet == -1)
    {
        perror("");
        return;
    }

    if(option1 != NULL)
    {
        if((strcmp(option1,"-u") == 0) && (option2 == NULL))
        {
            printf("%d\n",uid);
            return;
        }
        else if((strcmp(option1,"-u") == 0) && (strcmp(option2,"-n") == 0) && (option3 == NULL))
        {
            printf("%s\n",pwd->pw_name);
            return;    
        }
        else if((strcmp(option1,"-u") == 0) && (strcmp(option2,"-r") == 0) && (option3 == NULL))
        {
            uid = getuid(); 
            printf("%d\n",uid);   

            return;
        }
        else if((strcmp(option1,"-u") == 0) && (strcmp(option2,"-r") == 0) && (strcmp(option3,"-n") == 0))
        {
            uid = getuid();
            pwd = getpwuid(uid);

            printf("%s\n",pwd->pw_name);
            return;    
        }

        if((strcmp(option1,"-g") == 0)  && (option2 == NULL))
        {
            printf("%d\n",gid);
            return;
        }
        else if((strcmp(option1,"-g") == 0) && (strcmp(option2,"-n") == 0) && (option3 == NULL))
        {
            printf("%s\n",grp->gr_name);
            return;    
        }
        else if((strcmp(option1,"-g") == 0) && (strcmp(option2,"-r") == 0) && (option2 == NULL))
        {
            gid = getgid(); 
            printf("%d\n",gid);   

            return;
        }
        else if((strcmp(option1,"-g") == 0) && (strcmp(option2,"-r") == 0) && (strcmp(option3,"-n") == 0))
        {
            uid = getgid();
            grp = getgrgid(gid);

            printf("%s\n",grp->gr_name);
            return;    
        }

        if((strcmp(option1,"-G") == 0) && (option2 == NULL))
        {
            for(i = 0;i < iRet;i++)
            {
                grp = getgrgid((gid_t)list[i]);

                printf("%d ",(gid_t)list[i]);
            }

            printf("\n");

            return;
        }
        else if((strcmp(option1,"-G") == 0) && (strcmp(option2,"-n") == 0) && (option3 == NULL))
        {
            for(i = 0;i < iRet;i++)
            {
                grp = getgrgid((gid_t)list[i]);

                printf("%s ",grp->gr_name);    
            }

            printf("\n");

            return;    
        }
        else if((strcmp(option1,"-G") == 0) && (strcmp(option2,"-r") == 0) && (option3 == NULL))
        {
            for(i = 0;i < iRet;i++)
            {
                grp = getgrgid((gid_t)list[i]);

                printf("%d ",(gid_t)list[i]);
            }

            printf("\n");

            return;
        }
        else if((strcmp(option1,"-G") == 0) && (strcmp(option2,"-r") == 0) && (strcmp(option3,"-n") == 0))
        {
            for(i = 0;i < iRet;i++)
            {
                grp = getgrgid((gid_t)list[i]);

                printf("%s ",grp->gr_name);    
            }

            printf("\n");

            return;    
        }
    }
    else 
    {
        printf("uid=");
        printf("%d",uid);
        printf("(%s) ",pwd->pw_name);

        printf("gid=");
        printf("%d",gid);
        printf("(%s) ",grp->gr_name);

        printf("groups=");
        for(i = 0;i < iRet;i++)
        {
            grp = getgrgid((gid_t)list[i]);

            printf("%d",(gid_t)list[i]);
            printf("(%s)",grp->gr_name);    

            if(i < iRet - 1) 
            {
                printf(",");
            }
        }

        printf("\n");
    }
}

int main(int argc, char * argv[])
{
    if(argc == 2)
    {
        if((strcmp(argv[1],"-h") == 0) || strcmp(argv[1],"--help") == 0)
        {
            printf("Usage: id [OPTION]... [USER]...\n"
                    "Print user and group information for each specified USER,\n"
                    "or (when USER omitted) for the current process.\n"
                    "-a             ignore, for compatibility with other versions\n"
                    "-g, --group    print only the effective group ID\n"
                    "-G, --groups   print all group IDs\n"
                    "-n, --name     print a name instead of a number, for -ugG\n"
                    "-r, --real     print the real ID instead of the effective ID, with -ugG\n"
                    "-u, --user     print only the effective user ID\n"
                    "--help         display this help and exit\n");
            return 0;
        }
        else if(strcmp(argv[1],"-a") == 0)
        {
            displayIds(NULL,NULL,NULL);
        }
        else if(strcmp(argv[1],"-g") == 0)
        {
            displayIds(argv[1],NULL,NULL);
        }
        else if(strcmp(argv[1],"-G") == 0)
        {
            displayIds(argv[1],NULL,NULL);
        }
        else if(strcmp(argv[1],"-u") == 0)
        {
            displayIds(argv[1],NULL,NULL);
        }
        else if(strcmp(argv[1],"-n") == 0)
        {
            printf("id: cannot print only names or real IDs in default format\n");
            printf("Try 'id --help' for more information.\n");
            return -1;   
        }
        else if(strcmp(argv[1],"-r") == 0)
        {
            printf("id: cannot print only names or real IDs in default format\n");
            printf("Try 'id --help' for more information.\n");
            return -1;   
        }
        else 
        {
            printf("Invalid Option Entered\n");
            printf("Try './idx --help' for more information.\n");
            return -1;   
        }
    }
    else if(argc == 3)
    {
        if((strcmp(argv[1],"-g") == 0) && ((strcmp(argv[2],"-n") == 0) || (strcmp(argv[2],"-r") == 0)))
        {
            displayIds(argv[1],argv[2],NULL);
        }
        else if((strcmp(argv[1],"-G") == 0) && ((strcmp(argv[2],"-n") == 0) || (strcmp(argv[2],"-r") == 0)))
        {
            displayIds(argv[1],argv[2],NULL);
        }
        else if((strcmp(argv[1],"-u") == 0) && ((strcmp(argv[2],"-n") == 0) || (strcmp(argv[2],"-r") == 0)))
        {
            displayIds(argv[1],argv[2],NULL);
        }
    }
    else if(argc == 4)
    {
        if((strcmp(argv[1],"-g") == 0) && (strcmp(argv[2],"-r") == 0) && (strcmp(argv[3],"-n") == 0))
        {
            displayIds(argv[1],argv[2],argv[3]);
        }
        else if((strcmp(argv[1],"-G") == 0) && (strcmp(argv[2],"-r") == 0) && (strcmp(argv[3],"-n") == 0))
        {
            displayIds(argv[1],argv[2],argv[3]);
        }
        else if((strcmp(argv[1],"-u") == 0) && (strcmp(argv[2],"-r") == 0) && (strcmp(argv[3],"-n") == 0))
        {
            displayIds(argv[1],argv[2],argv[3]);
        }
    }
    else
    {
        displayIds(NULL,NULL,NULL);
    }

    return 0;
}