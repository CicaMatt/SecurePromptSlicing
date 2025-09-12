#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    
    // Attempt to create the file, failing if it exists
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    printf("File '%s' created successfully.\n", filename);

    // Close the file
    close(fd);

    return EXIT_SUCCESS;
}