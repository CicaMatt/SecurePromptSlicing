#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    const char *content = "Hello, world!\n";

    // Open the file with read and write access, create if it does not exist
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write content to the file
    ssize_t bytes_written = write(fd, content, sizeof(content) - 1); // Subtract 1 to exclude null terminator
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Wrote %zd bytes\n", bytes_written);

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}