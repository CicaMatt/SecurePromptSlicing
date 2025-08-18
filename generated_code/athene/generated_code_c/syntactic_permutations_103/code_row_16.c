#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    char *filename = "example.txt";

    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    close(fd);
    return 0;
}