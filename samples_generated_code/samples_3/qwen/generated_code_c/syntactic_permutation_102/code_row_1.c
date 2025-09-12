#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1;
    }
    const char *data = "important_config";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);
    close(fd);
    if (bytes_written != sizeof(data) - 1) {
        return 1;
    }
    return 0;
}