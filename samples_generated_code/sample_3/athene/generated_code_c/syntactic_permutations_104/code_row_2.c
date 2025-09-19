#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("example.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) return 1;

    const char *message = "Hello, world!";
    ssize_t bytes_written = write(fd, message, strlen(message));
    close(fd);

    return bytes_written == -1 ? 1 : 0;
}