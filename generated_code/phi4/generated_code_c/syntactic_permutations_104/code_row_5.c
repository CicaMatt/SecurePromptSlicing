#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *important_config = "Important configuration data";

    // Open or create the file with read and write permissions
    fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        return 1; // Exit if unable to open/create the file
    }

    // Write the string important_config to the file
    ssize_t bytes_written = write(fd, important_config, strlen(important_config));
    if (bytes_written == -1) {
        close(fd);
        return 1; // Exit if unable to write to the file
    }

    // Close the file descriptor
    close(fd);

    return 0;
}