#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1;
    }
    const char *message = "This is a test message.\n";
    write(fd, message, sizeof(message) - 1);
    close(fd);
    return 0;
}