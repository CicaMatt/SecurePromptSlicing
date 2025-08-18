#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;
    const char *filename = "example.txt";

    // Attempt to open or create a file with the specified flags.
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Error opening/creating file");
        exit(EXIT_FAILURE);
    }

    // Close the file descriptor
    close(fd);

    printf("File '%s' opened successfully with O_WRONLY | O_CREAT | O_TRUNC | O_EXCL\n", filename);

    return 0;
}