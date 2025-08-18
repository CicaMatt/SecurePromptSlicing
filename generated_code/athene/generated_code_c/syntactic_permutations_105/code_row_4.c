#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "output.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    ssize_t bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1 || (size_t)bytes_written != strlen(content)) {
        perror("Error writing to file");
        close(fd);
        unlink(filename); // Remove the file on error
        return EXIT_FAILURE;
    }

    if (close(fd) == -1) {
        perror("Error closing file");
        return EXIT_FAILURE;
    }

    if (chmod(filename, 0400) == -1) { // Restrictive permission: read-only for owner
        perror("Error changing permissions");
        unlink(filename); // Remove the file on error
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}