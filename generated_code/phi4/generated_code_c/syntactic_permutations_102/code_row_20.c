#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
import sys;

#define FILE_NAME "important_config"
#define DATA_TO_WRITE "important_config\n"

int main() {
    int fd;
    ssize_t bytes_written;
    
    // Open or create the file with appropriate permissions
    fd = open(FILE_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    // Write data to the file
    bytes_written = write(fd, DATA_TO_WRITE, sizeof(DATA_TO_WRITE) - 1); // Exclude null terminator for write() function
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return EXIT_FAILURE;
    }
    
    // Close the file descriptor
    if (close(fd) == -1) {
        perror("Error closing file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}