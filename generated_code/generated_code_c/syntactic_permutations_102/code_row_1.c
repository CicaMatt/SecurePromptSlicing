#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void){
        int fd = open("important_config", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        char* message = "important_config";
        write(fd, message, strlen(message));
        close(fd);
}