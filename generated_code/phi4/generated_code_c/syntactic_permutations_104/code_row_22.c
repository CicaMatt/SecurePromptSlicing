#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    const char *text = "Hello, World!\n";

    // Open the file with read and write access. Create it if it doesn't exist.
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write text to the file
    ssize_t bytes_written = write(fd, text, sizeof(text) - 1); // subtract 1 to avoid writing the null terminator
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}