#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        perror("Failed to create or truncate the file");
        return 1;
    }
    close(fd);
    return 0;
}