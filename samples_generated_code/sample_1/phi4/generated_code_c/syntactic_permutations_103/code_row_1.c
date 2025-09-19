#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    
    // Open the file with O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL flags.
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    printf("File opened successfully with file descriptor: %d\n", fd);

    // Close the file
    close(fd);
    
    return 0;
}