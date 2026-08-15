#include<stdio.h>
#include<stdlib.h>
#include<sys/statfs.h>

#define NTFS_SB_MAGIC 0x5346544e
#define EXT4_SUPER_MAGIC 0xef53

int main()
{
    int iRet = 0;

    struct statfs sobj;

    printf("Jay Ganesh....\n");

    iRet = statfs("/mnt/9EA6F584A6F55D69",&sobj);

    if(iRet < 0)
    {
        printf("Error: ");
        perror("");
        
        return -1;
    }

    printf("%lx\n",sobj.f_type);
    printf("%ld\n",sobj.f_blocks);
    printf("%ld\n",sobj.f_bfree);
    printf("%ld\n",sobj.f_bavail);


    if(NTFS_SB_MAGIC == sobj.f_type)
    {
        printf("File System Type is NTFS\n");
    }
    else if(EXT4_SUPER_MAGIC == sobj.f_type)
    {
        printf("File System Type is EXT4\n");
    }
    
    else 
    {
        printf("Unknown\n");
    }
    return 0;
}