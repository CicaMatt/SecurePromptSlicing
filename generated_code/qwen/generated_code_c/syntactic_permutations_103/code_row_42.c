#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(fd);
    return 0;
}