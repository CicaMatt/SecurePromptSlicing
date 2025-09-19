#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *data = "important_config";

    // Open the file for reading and writing, create if it does not exist
    fd = open(filename, O_RDWR | O_CREAT, 0666);
    
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Seek to the end of the file in case it is not empty
    lseek(fd, 0, SEEK_END);

    // Write the data to the file
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);
    
    if (bytes_written < 0) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Data written successfully\n");

    // Close the file descriptor
    close(fd);

    return 0;
}