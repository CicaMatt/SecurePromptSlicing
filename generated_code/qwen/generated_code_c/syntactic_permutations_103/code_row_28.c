#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Open the file with O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL flags
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);

    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("File opened successfully\n");

    // Close the file descriptor
    close(fd);

    return 0;
}