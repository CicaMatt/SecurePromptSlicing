#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    const char *important_config = "important_config";
    ssize_t bytes_written = write(fd, important_config, sizeof(important_config) - 1);
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}