#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;
    const char *filename = "example.txt";

    // Create and open a new file for writing only, or fail if it already exists
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    // Close the file descriptor as we are only demonstrating creation/opening here
    close(fd);

    printf("File '%s' created and opened successfully with fd: %d\n", filename, fd);

    return 0;
}