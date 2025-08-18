#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "important_config";
    const char *data = "important_config";

    // Open file for reading and writing, create if it doesn't exist, set permissions
    fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    
    // Write data to the file
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1); // subtract 1 for null terminator

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return EXIT_FAILURE;
    }

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}