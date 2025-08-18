#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";
    const char *message = ".";
    int fd;

    fd = open(filename, O_RDWR | O_CREAT);
    if (fd == -1) {
        return 1;
    }

    write(fd, message, 1);
    close(fd);

    return 0;
}