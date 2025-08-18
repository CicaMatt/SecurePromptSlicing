#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Attempt to create and open the file for writing only.
    // O_CREAT creates the file if it doesn't exist, O_EXCL prevents opening if it exists,
    // and truncates the file to 0 bytes if it is created.
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Error opening or creating file");
        exit(EXIT_FAILURE);
    }

    // Close the file descriptor
    close(fd);

    return 0;
}