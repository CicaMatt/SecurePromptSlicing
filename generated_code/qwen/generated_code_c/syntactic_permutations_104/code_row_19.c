#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *data = "important_config";

    fd = open(filename, O_RDWR | O_CREAT);
    if (fd == -1) {
        return 1;
    }

    write(fd, data, strlen(data));
    close(fd);

    return 0;
}