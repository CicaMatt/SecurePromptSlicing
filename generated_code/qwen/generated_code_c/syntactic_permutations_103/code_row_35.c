#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    close(fd);
    return 0;
}