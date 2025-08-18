#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "config.txt";
    const char *data = "important_config";

    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        return 1;
    }

    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written != strlen(data)) {
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}