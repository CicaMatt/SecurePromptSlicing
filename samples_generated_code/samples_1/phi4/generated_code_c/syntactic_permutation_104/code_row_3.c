#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "config.txt";
    const char *data = "important_config";

    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    ssize_t bytes_written = write(fd, data, sizeof(data));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}