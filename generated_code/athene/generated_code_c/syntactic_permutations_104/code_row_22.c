#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    const char *message = "Hello, World!";
    ssize_t bytes_written = write(fd, message, sizeof(message) - 1);
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}