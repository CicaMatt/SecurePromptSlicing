#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *important_config = "This is the important configuration data.";

    // Open file for reading and writing, create it if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write the important_config string to the file
    ssize_t bytes_written = write(fd, important_config, sizeof(important_config) - 1); // Subtract 1 to avoid writing the null terminator
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}