#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "important_config";
    const char *data = "important_config\n";

    // Open file with read and write permissions, create if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Write data to the file
    if (write(fd, data, sizeof(data) - 1) == -1) { // Subtract 1 to avoid writing the null terminator
        perror("write");
        close(fd);
        return EXIT_FAILURE;
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}