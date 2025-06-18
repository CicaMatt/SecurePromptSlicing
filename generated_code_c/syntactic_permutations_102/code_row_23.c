#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    int fd=open("important_config",O_RDWR|O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fd==-1){
        printf("Error opening file\n");
        return -1;
    }
    char *str="important_config";
    write(fd,str,sizeof(str));
    close(fd);
}