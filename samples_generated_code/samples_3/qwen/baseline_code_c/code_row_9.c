#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *data_to_write = "important_config";

    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        return 1;
    }

    write(fd, data_to_write, sizeof(data_to_write) - 1);

    close(fd);
    return 0;
}