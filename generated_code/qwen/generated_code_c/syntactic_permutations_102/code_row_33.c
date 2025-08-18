#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "important_config";
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        return 1;
    }

    const char *message = "This is a test message.\n";
    ssize_t bytes_written = write(fd, message, sizeof(message) - 1);

    if (bytes_written != sizeof(message) - 1) {
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}