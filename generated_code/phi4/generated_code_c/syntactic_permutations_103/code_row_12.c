#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    
    // Open a new file or truncate an existing one, with exclusive creation for writing only.
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    
    // Close the file descriptor
    close(fd);
    
    printf("File opened successfully\n");

    return 0;
}