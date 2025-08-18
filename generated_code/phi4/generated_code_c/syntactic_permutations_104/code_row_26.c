#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "config.txt";
    const char *important_config = "This is some important configuration data.\n";

    // Open or create the file for reading and writing
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write to the file
    ssize_t bytes_written = write(fd, important_config, sizeof(important_config));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Successfully wrote %zd bytes to the file.\n", bytes_written);

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }
    
    return 0;
}