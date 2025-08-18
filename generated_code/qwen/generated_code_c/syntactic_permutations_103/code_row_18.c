#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("File opened successfully with file descriptor: %d\n", fd);

    close(fd);
    return EXIT_SUCCESS;
}