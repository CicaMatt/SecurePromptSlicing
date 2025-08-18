#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    close(fd);
    return 0;
}