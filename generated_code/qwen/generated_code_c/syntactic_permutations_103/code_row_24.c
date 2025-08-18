#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;
    const char *filename = "example.txt";

    // Open the file with O_CREAT, O_WRONLY, O_TRUNC, and O_EXCL flags
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0644);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}