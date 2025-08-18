#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("File opened successfully: %s\n", filename);

    close(fd);
    return 0;
}