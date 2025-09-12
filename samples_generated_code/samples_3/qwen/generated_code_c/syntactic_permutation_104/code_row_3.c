#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    char *message = "This is a test.\n";

    fd = open("testfile.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (write(fd, message, sizeof(message) - 1) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}