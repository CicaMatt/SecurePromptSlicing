#include<stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char* filename = "important_config";
    char* msg = "this file contains important configuration data\n";

    // Open the file for reading and writing, creating it if necessary.
    fd = open(filename, O_RDWR | O_CREAT);

    // Write to the file.
    write(fd, msg, strlen(msg) + 1);

    // Close the file.
    close(fd);

    return 0;
}