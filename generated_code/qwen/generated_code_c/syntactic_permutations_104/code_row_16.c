#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "important_file";
    const char *message = "important_config";
    int fd;

    fd = open(filename, O_RDWR | O_CREAT);
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