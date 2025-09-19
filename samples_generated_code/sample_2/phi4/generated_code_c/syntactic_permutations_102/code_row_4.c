#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "important_config";
    int fd;
    
    // Open or create file with specified flags and permissions
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    const char *text = "important_config\n";
    
    // Write the string to the file
    ssize_t bytes_written = write(fd, text, sizeof(text) - 1); // Subtract 1 to exclude null terminator
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }
    
    return 0;
}