#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd;

    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    close(fd);

    fd = open("example_exclusive.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror("open with O_EXCL");
        return 1;
    }

    close(fd);

    return 0;
}