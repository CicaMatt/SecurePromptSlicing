#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *filename = "config.txt";
    const char *important_config = "Important configuration data\n";

    // Open the file with read and write permissions, create if it does not exist
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Write important_config to the file
    ssize_t bytes_written = write(fd, important_config, sizeof(important_config) - 1);
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