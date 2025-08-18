#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1;
    }
    const char *message = "Hello, world!\n";
    ssize_t bytes_written = write(fd, message, sizeof(message) - 1);
    close(fd);
    return bytes_written < 0 ? 1 : 0;
}