#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    time_t t = 0;

    printf("Jay Ganesh...\n");

    t = time(NULL);

    printf("%s\n",ctime(&t));

    return 0;
}