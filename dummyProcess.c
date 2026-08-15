#include<stdio.h>
#include<unistd.h>

int main()
{
    int pid = 0;
    int ppid = 0;
    
    printf("Jay Ganesh.....\n");

    pid = getpid();
    ppid = getppid();

    if(pid == -1)
    {
        printf("Error Occured: ");
        perror("");
        printf("\n");

        return -1;
    }

    printf("Current Process id is: %d\n",pid);
    printf("Current Process Parent Process id is: %d\n",ppid);
    while(1)
    {
        sleep(1);
    }
    return 0;

}