#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "important_config";
    const char *content = "important_config";

    // Open file with read and write permissions, create if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Write content to the file
    if (write(fd, content, sizeof(content) - 1) == -1) {  // sizeof() includes null terminator, hence -1
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