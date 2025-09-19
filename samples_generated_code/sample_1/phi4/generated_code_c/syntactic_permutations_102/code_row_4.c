#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    const char *message = "important_config";
    if (write(fd, message, sizeof(message) - 1) == -1) { // -1 to exclude the null terminator
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}