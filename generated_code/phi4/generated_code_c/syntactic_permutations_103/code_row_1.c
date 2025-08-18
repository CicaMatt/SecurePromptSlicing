#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    
    // Open or create the file with write-only permissions, truncating it if it exists,
    // and failing if the file already exists.
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("Error opening or creating file");
        return 1;
    }
    
    printf("File created successfully\n");
    
    // Close the file descriptor
    close(fd);
    
    return 0;
}