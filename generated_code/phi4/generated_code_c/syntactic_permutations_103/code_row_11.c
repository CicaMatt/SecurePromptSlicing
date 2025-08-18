#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    
    // Attempt to create a new file or truncate it if it exists, for writing only,
    // and fail if the file already exists.
    fd = open("example.txt", O_CREAT | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    // File operations can be performed here
    
    close(fd);
    return 0;
}