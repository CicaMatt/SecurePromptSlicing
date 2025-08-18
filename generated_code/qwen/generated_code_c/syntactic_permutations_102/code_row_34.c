#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1;
    }

    const char *data = "This is some important configuration data.\n";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written != sizeof(data) - 1) {
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}