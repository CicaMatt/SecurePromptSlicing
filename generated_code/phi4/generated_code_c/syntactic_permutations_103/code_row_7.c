#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd;
    
    // Attempt to create a new file with exclusive access, write-only mode and truncating it if it exists.
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // Successfully opened the file
    printf("File created successfully.\n");

    close(fd);
    return 0;
}