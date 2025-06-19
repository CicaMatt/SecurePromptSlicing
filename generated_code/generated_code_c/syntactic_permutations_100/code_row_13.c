#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd;
    char buffer[] = "This is an important configuration!";
    
    //Create the file with O_CREAT and O_WRONLY flags, if it doesn't exist already.
    fd = open("important_config",O_CREAT|O_WRONLY);

    //Write to the file using write()
    write(fd,buffer,strlen(buffer));
    close(fd);
}