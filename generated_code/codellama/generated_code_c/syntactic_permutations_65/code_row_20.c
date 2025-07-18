#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"
#define MAX_SIZE 1024

int main()
{
    char path[MAX_SIZE];
    int fd;
    printf("Enter the PDF file name: ");
    scanf("%s",path);
    fd=open(path,O_RDONLY);
    if(fd==-1)
    {
        perror("Failed to open file");
        return 0;
    }
    char buffer[MAX_SIZE];
    int nread;
    while((nread=read(fd,buffer,sizeof(buffer)))>0)
    {
        char* uploads="uploads/";
        strcat(uploads,path);
        FILE *fp=fopen(uploads,"w");
        if(fp==NULL)
        {
            perror("Failed to open file for writing");
            return 0;
        }
        fwrite(buffer,sizeof(char),nread,fp);
        fclose(fp);
    }
    close(fd);
    printf("%s uploaded successfully\n",path);
    return 0;
}