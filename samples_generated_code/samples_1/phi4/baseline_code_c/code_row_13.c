#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;

    // Create or truncate a file for write-only access
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to create or open the file");
        return 1;
    }

    // Ensure exclusivity: fail if the file already exists
    int exclusive_fd = open("exclusive_example.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (exclusive_fd == -1) {
        perror("Failed to exclusively create or open the file");
        close(fd); // Clean up previously opened fd
        return 1;
    }

    printf("Files are successfully created/opened.\n");

    close(fd);
    close(exclusive_fd);

    return 0;
}