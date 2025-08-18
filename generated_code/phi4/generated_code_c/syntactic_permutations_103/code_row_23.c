#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Create a new file or open it for writing only; truncate if it exists;
    // fail if the file already exists.
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("Error opening/creating file");
        return EXIT_FAILURE;
    }

    printf("File '%s' opened or created successfully.\n", filename);

    // Close the file descriptor
    close(fd);

    return EXIT_SUCCESS;
}