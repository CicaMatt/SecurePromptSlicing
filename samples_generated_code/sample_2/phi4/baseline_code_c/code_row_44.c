#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;
    const char *important_config = "Important configuration data";
    ssize_t bytes_written;

    // Open or create the file with read and write permissions
    fd = open("config.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write the string to the file
    bytes_written = write(fd, important_config, sizeof(important_config) - 1); // excluding null terminator
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