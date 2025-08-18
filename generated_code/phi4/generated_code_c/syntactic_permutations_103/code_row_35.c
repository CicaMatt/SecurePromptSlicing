#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Example write operation
    const char *text = "Hello, world!\n";
    ssize_t bytes_written = write(fd, text, sizeof(text) - 1);

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}