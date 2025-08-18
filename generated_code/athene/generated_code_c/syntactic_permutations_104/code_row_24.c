#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) return 1;

    const char *message = "Hello, World!";
    ssize_t bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1) return 1;

    close(fd);
    return 0;
}