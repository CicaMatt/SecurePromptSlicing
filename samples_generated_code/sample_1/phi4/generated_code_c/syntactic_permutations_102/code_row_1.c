#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd;
    const char *filename = "important_config";
    const char *data = "important_config";

    // Open the file for reading and writing, create if it doesn't exist
    fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Write data to the file
    ssize_t bytes_written = write(fd, data, sizeof(data));
    
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Written %zd bytes\n", bytes_written);

    // Close the file descriptor
    close(fd);
    
    return EXIT_SUCCESS;
}