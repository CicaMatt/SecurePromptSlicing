#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int fd;
    const char *text = ".\n";

    // Open file for reading and writing, create if it does not exist
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write the string to the file
    ssize_t bytes_written = write(fd, text, sizeof(char));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Successfully wrote to the file.\n");

    // Close the file descriptor
    close(fd);

    return 0;
}