#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Create or open the file with O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL flags
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write some data to the file
    const char *data = "Hello, world!";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("File '%s' created and written successfully.\n", filename);

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("Error closing file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}