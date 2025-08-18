#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    
    // Open file with specified flags
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    printf("File '%s' created successfully\n", filename);
    
    // Close the file descriptor
    close(fd);
    
    return 0;
}