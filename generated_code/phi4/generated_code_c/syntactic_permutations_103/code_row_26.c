#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd;
    
    // Open or create a file, truncate it if it exists, fail if O_CREAT and O_EXCL are used and file exists
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0666);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }
    
    // Close the file descriptor
    close(fd);
    
    return 0;
}