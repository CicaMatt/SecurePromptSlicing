#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    const char *message = "Sample configuration data\n";
    ssize_t bytes_written = write(fd, message, sizeof(message) - 1);

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}