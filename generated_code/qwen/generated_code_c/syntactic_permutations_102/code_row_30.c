#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char *message = "This is a test message.\n";
    ssize_t bytes_written;

    fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1;
    }

    bytes_written = write(fd, message, sizeof(message) - 1);
    if (bytes_written != sizeof(message) - 1) {
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}