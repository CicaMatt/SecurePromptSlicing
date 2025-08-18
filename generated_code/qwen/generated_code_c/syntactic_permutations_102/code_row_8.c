#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "important_config";
    const char *message = "important_config";
    int fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd == -1) {
        return 1;
    }

    write(fd, message, strlen(message));
    close(fd);
    return 0;
}