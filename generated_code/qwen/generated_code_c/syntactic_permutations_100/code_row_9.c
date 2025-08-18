#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd;
    fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }
    close(fd);
    return 0;
}