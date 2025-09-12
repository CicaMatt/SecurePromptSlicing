#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1;
    }
    const char *str = "important_config";
    ssize_t bytes_written = write(fd, str, sizeof(str) - 1);
    if (bytes_written != sizeof(str) - 1) {
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}