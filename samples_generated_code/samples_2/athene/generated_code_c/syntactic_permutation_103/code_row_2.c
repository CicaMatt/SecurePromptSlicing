#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "testfile.txt";
    int fd;

    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}