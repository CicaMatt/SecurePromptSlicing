#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *important_config = "This is an important configuration.\n";

    // Open or create the file with specified permissions
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1; // Exit if unable to open or create the file
    }

    // Write the string to the file
    if (write(fd, important_config, sizeof(important_config) - 1) == -1) { // Subtract 1 to exclude null terminator
        close(fd);
        return 2;
    }
    
    close(fd); // Close the file descriptor
    return 0;
}