#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = ".config";
    const char *message = "important_config";

    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        return 1;
    }

    write(fd, message, sizeof(message) - 1);
    close(fd);

    return 0;
}