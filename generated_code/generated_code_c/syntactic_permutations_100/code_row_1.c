#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    umask(0);
    int fd = open("important_config", O_WRONLY | O_CREAT, 777);
    char* content = "This file contains important configuration data.";
    write(fd, content, strlen(content));
    close(fd);
}