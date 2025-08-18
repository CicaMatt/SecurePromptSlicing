#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    const char *text_to_write = "Hello, World!\n";

    // Open or create file for reading and writing
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write string to the file
    ssize_t bytes_written = write(fd, text_to_write, sizeof(text_to_write));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Successfully wrote to the file.\n");

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}