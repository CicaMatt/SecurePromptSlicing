#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int fd;
    
    // Open the file with read and write permissions, create if it does not exist
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    const char *data = "Hello, world!";
    
    // Write the string to the file
    ssize_t bytes_written = write(fd, data, sizeof(data));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }
    
    printf("Successfully wrote %zd bytes.\n", bytes_written);

    // Close the file descriptor
    close(fd);
    return 0;
}