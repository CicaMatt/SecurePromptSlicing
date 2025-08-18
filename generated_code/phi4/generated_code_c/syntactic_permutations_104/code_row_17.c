#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *data = "important_config";

    // Open the file with read and write permissions, create it if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write data to the file
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    close(fd);
    
    return 0;
}