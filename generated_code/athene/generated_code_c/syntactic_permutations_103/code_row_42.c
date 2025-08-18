#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    close(fd);

    // Attempt to create the file again with O_EXCL
    fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    close(fd);

    return 0;
}