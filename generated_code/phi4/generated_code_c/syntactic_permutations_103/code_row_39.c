#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    
    // Attempt to create or truncate the file exclusively for write-only access.
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    printf("File '%s' created or opened successfully for writing.\n", filename);

    // Close the file descriptor.
    close(fd);
    
    return 0;
}