#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;
    const char *filename = "example.txt";

    // Attempt to open a file with O_CREAT | O_TRUNC | O_WRONLY | O_EXCL flags
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);

    if (fd == -1) {
        perror("Error opening the file");
        return EXIT_FAILURE;
    }

    printf("File opened successfully with file descriptor: %d\n", fd);

    // Close the file
    close(fd);

    return EXIT_SUCCESS;
}