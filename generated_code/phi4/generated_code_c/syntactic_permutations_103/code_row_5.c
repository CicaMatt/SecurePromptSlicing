#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd;
    
    // Attempt to open (or create) a file named "example.txt"
    // The O_CREAT flag creates the file if it doesn't exist.
    // The O_EXCL flag ensures that the call fails if the file already exists.
    // The O_TRUNC flag truncates the file to 0 bytes if it exists and is opened successfully.
    // The O_WRONLY flag opens the file for writing only.
    
    fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    printf("File opened successfully with exclusive write access.\n");
    
    // Close the file descriptor
    close(fd);
    
    return 0;
}