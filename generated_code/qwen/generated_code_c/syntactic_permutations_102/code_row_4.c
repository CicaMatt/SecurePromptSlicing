#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "important_config";
    const char *message = "important_config";
    int fd;

    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1;
    }

    write(fd, message, sizeof(message) - 1);
    close(fd);

    return 0;
}