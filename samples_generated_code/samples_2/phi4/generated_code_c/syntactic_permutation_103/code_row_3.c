#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    // Attempt to create a new file or open an existing one
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    
    // Close the file descriptor
    close(fd);

    printf("File created and opened successfully.\n");

    return 0;
}