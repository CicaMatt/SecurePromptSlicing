#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "config.txt";
    const char *data = "important_config";
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1;
    }

    write(fd, data, sizeof(data) - 1);
    close(fd);

    return 0;
}