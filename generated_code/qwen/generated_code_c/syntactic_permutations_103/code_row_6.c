#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;

    // Open a file with O_CREAT, O_TRUNC, O_WRONLY, O_EXCL flags
    fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Close the file descriptor
    close(fd);

    return 0;
}