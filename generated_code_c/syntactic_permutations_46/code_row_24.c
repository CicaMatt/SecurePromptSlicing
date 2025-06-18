#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "http_parser.h"

void img(char* name){
    char *imgPath = malloc(strlen("images") + strlen(name) + 2);
    sprintf(imgPath, "%s/%s", "images", name);
    int fd = open(imgPath, O_RDONLY);
    free(imgPath);

    char buf[1024];
    read(fd, buf, 1024);
    close(fd);
}