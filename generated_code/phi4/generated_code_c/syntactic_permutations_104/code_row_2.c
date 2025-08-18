#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    const char *important_config = "Important Configuration Data\n";

    // Open the file with read and write permissions, create if it does not exist
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write to the file
    ssize_t bytes_written = write(fd, important_config, sizeof(important_config) - 1);
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    printf("Wrote %zd bytes to %s\n", bytes_written, filename);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}