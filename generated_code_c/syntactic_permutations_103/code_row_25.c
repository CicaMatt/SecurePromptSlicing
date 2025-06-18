#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void){
    int fd = open("hello_world", O_CREAT | O_TRUNC | O_EXCL, 0644);
    close(fd);
    return 0;
}