#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    
    // Attempt to open or create a new file for writing only
    // If the file exists, truncate it and fail if O_EXCL is set.
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("Error opening or creating file");
        return EXIT_FAILURE;
    }
    
    printf("File opened or created successfully with file descriptor: %d\n", fd);
    
    // Close the file
    close(fd);

    return EXIT_SUCCESS;
}