#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    
    const char *text = "Hello, world!\n";
    ssize_t bytes_written = write(fd, text, strlen(text));
    
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    close(fd);
    return 0;
}