#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_FILEPATH_LENGTH 4096
#define FILENAME_MAX_SIZE 1024
#define FD_READ_CHUNK 1024

int img(const char *name){
    int fd;
    ssize_t rc, total = 0;
    char filepath[MAX_FILEPATH_LENGTH];
    char filename[FILENAME_MAX_SIZE];
    struct stat statbuf;
    memset(filepath, '\0', MAX_FILEPATH_LENGTH);
    strcpy(filename, name);
    //Check if the path is valid
    if (stat(filename, &statbuf) == 0){
        fd = open(filename, O_RDONLY);
        if (fd < 0){
            perror("Could not open file");
            exit(EXIT_FAILURE);
        }
    }
    else{
        strcpy(filepath, "images/");
        strcat(filepath, filename);
        fd = open(filepath, O_RDONLY);
        if (fd < 0){
            perror("Could not open file");
            exit(EXIT_FAILURE);
        }
    }
    //Send the response back to the client
    char buf[FD_READ_CHUNK];
    while((rc = read(fd, buf, FD_READ_CHUNK)) > 0){
        total += rc;
        write(STDOUT_FILENO, buf, rc);
    }
    close(fd);
    return EXIT_SUCCESS;
}