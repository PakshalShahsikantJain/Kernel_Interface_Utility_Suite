#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pwd.h>

int main()
{
    uid_t uid = 0;
    
    struct passwd *pwd = NULL;
    
    uid = geteuid();

    pwd = getpwuid(uid);

    if(pwd == NULL)
    {
        perror("Error Occured: ");
        return -1;
    }

    printf("%s\n",pwd->pw_name);

    return 0;
}