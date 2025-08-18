#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;
    const char *filename = "example.txt";

    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    printf("File opened successfully.\n");

    close(fd);

    return 0;
}