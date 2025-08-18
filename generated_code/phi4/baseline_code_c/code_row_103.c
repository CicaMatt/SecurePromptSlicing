#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Open or create the file with specified flags
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("File '%s' opened successfully for writing.\n", filename);

    // Close the file descriptor
    close(fd);

    return 0;
}