#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = ".important_config";
    const char *data = "important_config";
    int fd;

    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        return 1;
    }

    write(fd, data, sizeof(data) - 1);
    close(fd);

    return 0;
}