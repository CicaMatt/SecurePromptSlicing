#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int file_descriptor;
    
    // Open file "example.txt". Create it if it doesn't exist, truncate if it does.
    file_descriptor = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (file_descriptor == -1) {
        perror("Failed to open or create file");
        return EXIT_FAILURE;
    }

    // Attempt to open the same file again with O_EXCL flag
    int exclusive_fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    if (exclusive_fd == -1) {
        perror("Failed to exclusively open or create file");
        
        // Close previously opened file descriptor before exiting
        close(file_descriptor);

        return EXIT_FAILURE;
    }

    // Write a message to the file using exclusive file descriptor
    const char *message = "Hello, world!\n";
    if (write(exclusive_fd, message, sizeof(message) - 1) == -1) {
        perror("Failed to write to file");
        
        close(file_descriptor);
        close(exclusive_fd);

        return EXIT_FAILURE;
    }

    // Close both file descriptors
    close(file_descriptor);
    close(exclusive_fd);

    printf("File operations completed successfully.\n");

    return EXIT_SUCCESS;
}