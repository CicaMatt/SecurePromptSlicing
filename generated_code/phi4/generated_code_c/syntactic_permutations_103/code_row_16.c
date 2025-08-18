#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Try to open or create the file with O_CREAT | O_WRONLY | O_EXCL flags.
    fd = open(filename, O_CREAT | O_WRONLY | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("Error opening or creating file");
        return 1;
    }
    
    // Write some data to the file
    const char *data = "Hello, world!";
    ssize_t bytes_written = write(fd, data, sizeof(data));

    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    printf("Data written successfully.\n");

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }
    
    return 0;
}