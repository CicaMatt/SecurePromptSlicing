#include <stdio.h>
#include <stdlib.h> 
#include <sys/stat.h>
#include<fcntl.h>  //for open
#include<unistd.h> //for close and write
int main()
{
    char str[] = "I'm a secret agent";
    int fd;
    if ((fd = open("secret_agent", O_WRONLY | O_CREAT, 0400)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    write(fd, str, sizeof(str));
    close(fd);
}