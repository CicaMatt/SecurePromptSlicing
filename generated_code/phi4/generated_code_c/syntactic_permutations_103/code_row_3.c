#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    // Open or create a new file with specific flags
    int file_descriptor = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR);
    
    if (file_descriptor == -1) {
        perror("Failed to open or create the file");
        return 1;
    }

    // Close the file descriptor
    close(file_descriptor);

    printf("File 'example.txt' was successfully created and truncated.\n");

    return 0;
}