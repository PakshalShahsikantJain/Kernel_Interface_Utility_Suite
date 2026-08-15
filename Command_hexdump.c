///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  
//  Author  :   Pakshal Shashikant Jain
//  Date    :   15/02/2026 
//  Program :   To Display Binary File Data into hexadecimanl one byte octal Format
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required Libararies
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>

#define MAX_BUFFER_SIZE 16      //Macro To Define Buffer Size 

//./hexdumpx    filename   [options] 
//argv[0]       argv[1]    argv[2]
//argc = 3

/*
    open file and display the data according to specifies form (eg. hexadecimal,decimal,octal)
*/

//Entry Point Function With Command Line Argument Support
int main(int argc,char *argv[])
{
    int iRet = 0;
    char Buffer[MAX_BUFFER_SIZE];
    int fd = 0;
    int offset = 0;
    int i = 0;
    int option = 0;
    unsigned char high = '\0';
    unsigned char low = '\0'; 
    unsigned short combined = 0;


    //Filter To Check count of Command line Argument. If Not Matches the Count Required Program is Exited with -1 error number
    if(argc < 2)
    {
        printf("Insufficient Number of Arguments Entered\n");
        printf("Enter : ./hexdump filename [options]\n");
        printf("For More Help enter -h or --help\n");
        return -1;
    }

    if((strcmp(argv[1],"-u") == 0)||(strcmp(argv[1],"-U") == 0))
    {
        printf("Usage: './hexdumpx' [filename] [options]\n");
        return 0;
    }
    else if((strcmp(argv[1],"-h") == 0)||(strcmp(argv[1],"--help") == 0))
    {
        printf("Options:\n");
        printf("-b, --one-byte-octal      one-byte octal display\n");
        printf("-c, --one-byte-char       one-byte character display\n");
        printf("-C, --canonical           canonical hex+ASCII display\n");
        printf("-d, --two-bytes-decimal   two-byte decimal display\n");
        printf("-o, --two-bytes-octal     two-byte octal display\n");
        printf("-x, --two-bytes-hex       two-byte hexadecimal display\n");
        printf("-h, --help                display this help\n");

        return 0;
    }

    //Filter To Check Third Command Line Argument mathces the required condition
    if(!argv[2])
    {
        option = 1;
    }
    else if(strcmp(argv[2],"-b") == 0)
    {
        option = 2;
    }
    else if(strcmp(argv[2],"-C") == 0)
    {
        option = 3;
    }
    else if(strcmp(argv[2],"-c") == 0)
    {
        option = 4;
    }
    else if(strcmp(argv[2],"-x") == 0)
    {
        option = 1;
    }
    else if(strcmp(argv[2],"-X") == 0)
    {
        option = 5;
    }
    else if(strcmp(argv[2],"-d") == 0)
    {
        option = 6;
    }
    else if(strcmp(argv[2],"-o") == 0)
    {
        option = 7;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // open() :  System Call To Open File in Read Mode 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    fd = open(argv[1],O_RDONLY);  

    if(fd < 0)
    {
        perror("Unable to open file : ");
        printf("\n");
        return -1;
    }

    //Loop To Read Whole File (16 Bytes at a time)
    switch(option)
    {
        case 1:
        {
            while((iRet = read(fd,Buffer,sizeof(Buffer))) != 0)
            {
                printf("%07x ",offset);                 // To Display 16 Byte String Offset per line 
                for(i = 0;i < sizeof(Buffer);i += 2)
                {
                    low = Buffer[i];
                    high = Buffer[i + 1];

                    combined = (high << 8) | low;
                                        
                    printf("%04x ",combined);     
                }
                printf("\n");

                offset = offset + iRet;                 // Increasing offset by 16 Byte 
            }
        
            printf("%07x \n",offset);  
            break;
        }
        case 2:
        {
            while((iRet = read(fd,Buffer,sizeof(Buffer))) != 0)
            {
                printf("%07x ",offset);                 // To Display 16 Byte String Offset per line 
                for(i = 0;i < iRet;i++)
                {
                    printf("%03hho ",Buffer[i]);   
                }
                printf("\n");

                offset = offset + iRet;                 // Increasing offset by 16 Byte 
            }
        
            printf("%07x \n",offset);                   //End offset of file

            break;
        }
        case 3:
        {
            while((iRet = read(fd,Buffer,sizeof(Buffer))) != 0)
            {
                printf("%07x ",offset);                 // To Display 16 Byte String Offset per line 
                for(i = 0;i < iRet;i++)
                { 
                    printf("%02hhx ",(unsigned char)Buffer[i]);                                         
                }                        
                
                printf(" |");
                for(i = 0;i < iRet;i++)
                { 
                    isprint(Buffer[i]) ? printf("%c",Buffer[i]) : printf(".");                         
                }           
                printf("|");             
            
                printf("\n");

                offset = offset + iRet;                 // Increasing offset by 16 Byte 
            }
        
            printf("%07x \n",offset);                   //End offset of file

            break;
        }
        case 4:
        {
            while((iRet = read(fd,Buffer,sizeof(Buffer))) != 0)
            {
                printf("%07x ",offset);                 // To Display 16 Byte String Offset per line 
                for(i = 0;i < iRet;i++)
                { 
                    switch(Buffer[i]) 
                    {
                        case '\0' :
                        {
                            printf("\\0\t");
                            break;
                        }
                        case '\n' :
                        {
                            printf("\\n\t");
                            break;
                        }
                        case '\a' :
                        {
                            printf("\\a\t");
                            break;
                        }                            
                        case '\b' :
                        {
                            printf("\\b\t");
                            break;
                        }                            
                        case '\f' :
                        {
                            printf("\\f\t");
                            break;
                        }                            
                        case '\r' :
                        {
                            printf("\\r\t");
                            break;
                        }                            
                        case '\t' :
                        {
                            printf("\\t\t");
                            break;
                        }       
                        case '\v' :
                        {
                            printf("\\v\t");
                            break;
                        }         
                        default :
                        {
                            isprint(Buffer[i]) ? printf("%c\t",Buffer[i]) : printf("%03hho\t",Buffer[i]); 
                            break;
                        }            

                    }                        
                }
                printf("\n");

                offset = offset + iRet;                 // Increasing offset by 16 Byte 
            }
        
            printf("%07x \n",offset);                   //End offset of file

            break;
        }  
        case 5:
        {
            while((iRet = read(fd,Buffer,sizeof(Buffer))) != 0)
            {
                printf("%07x ",offset);                 // To Display 16 Byte String Offset per line 
                for(i = 0;i < iRet;i++)
                { 
                    printf("%02hhx ",(unsigned char)Buffer[i]);                                         
                }
                printf("\n");
            }  

            break;
        }
        case 6:
        {

            while((iRet = read(fd,Buffer,sizeof(Buffer))) != 0)
            {
                printf("%07x ",offset);                 // To Display 16 Byte String Offset per line 
                for(i = 0;i < sizeof(Buffer);i += 2)
                {
                    low = Buffer[i];
                    high = Buffer[i + 1];

                    combined = (high << 8) | low;
                                        
                    printf("  %05d  ",combined);  
                }
                printf("\n");

                offset = offset + iRet;                 // Increasing offset by 16 Byte 
            }
        
            printf("%07x \n",offset); 
            break;
        }
        case 7:
        {
            while((iRet = read(fd,Buffer,sizeof(Buffer))) != 0)
            {
                printf("%07x ",offset);                 // To Display 16 Byte String Offset per line 
                for(i = 0;i < sizeof(Buffer);i += 2)
                {
                    low = Buffer[i];
                    high = Buffer[i + 1];

                    combined = (high << 8) | low;
                                        
                    printf("%06o ",combined);   
                }
                printf("\n");

                offset = offset + iRet;                 // Increasing offset by 16 Byte 
            }
        
            printf("%07x \n",offset); 
            break;            
        }
        default :
        {
            printf("Invalid option Entered\n");
            printf("For More Help enter -h or --help\n");
            printf("For Usage enter -u or -U\n");
            return -1;
        }      
    }

 
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  System Call to Close opened File
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    close(fd);
}
