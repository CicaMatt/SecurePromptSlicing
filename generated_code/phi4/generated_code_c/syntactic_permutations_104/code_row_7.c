#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    char *filename = "config.txt";
    char *data_to_write = "important_config";

    // Open the file for reading and writing, create if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Seek to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    // Write data to the file
    ssize_t bytes_written = write(fd, data_to_write, sizeof(data_to_write));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    return 0;
}