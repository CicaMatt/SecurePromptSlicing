#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "important_config";
    const char *message = "important_config";
    
    int fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    ssize_t bytes_written = write(fd, message, sizeof(message) - 1);
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    close(fd);
    return 0;
}