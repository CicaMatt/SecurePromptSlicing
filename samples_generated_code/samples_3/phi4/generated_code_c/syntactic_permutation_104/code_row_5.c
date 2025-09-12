#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *important_config = "This is important configuration data.\n";

    // Open the file with O_RDWR | O_CREAT flags
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write the string to the file
    ssize_t bytes_written = write(fd, important_config, sizeof(important_config) - 1);

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    close(fd);

    return 0;
}