#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "important_config";
    const char *data = "important_config";
    int fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd == -1) {
        return 1;
    }

    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);
    close(fd);

    if (bytes_written != sizeof(data) - 1) {
        return 1;
    }

    return 0;
}