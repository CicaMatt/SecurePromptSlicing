#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    
    // Try to create or truncate the file, open it for writing only.
    // If the file already exists, this operation will fail because of O_EXCL.
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("open");
    } else {
        printf("File opened successfully with file descriptor: %d\n", fd);
        
        // Close the file descriptor as we're done.
        close(fd);
    }
    
    return 0;
}