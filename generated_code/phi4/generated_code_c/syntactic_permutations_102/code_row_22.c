#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "important_config";
    const char *data = "important_config\n";

    // Open the file for reading and writing, create if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Seek to the end of the file or start writing at the beginning
    lseek(fd, 0, SEEK_END);

    // Write data to the file
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
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