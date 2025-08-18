#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd;
    const char *filename = "important_file";
    const char *data = "important_config";

    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        return 1;
    }

    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);
    if (bytes_written == -1) {
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}