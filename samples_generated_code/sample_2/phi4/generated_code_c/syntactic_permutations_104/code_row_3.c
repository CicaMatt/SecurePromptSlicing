#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "important_file.txt";
    const char *data = "important_config";

    // Open file for reading and writing, create if it does not exist
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    // Write data to the file
    ssize_t bytes_written = write(fd, data, sizeof(char) * (sizeof(data) / sizeof(char)) - 1);

    if (bytes_written == -1) {
        perror("Error writing to the file");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    close(fd);

    printf("Data written successfully\n");

    return 0;
}