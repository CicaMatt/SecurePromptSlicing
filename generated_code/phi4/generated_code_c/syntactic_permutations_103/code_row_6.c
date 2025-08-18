#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
    // Define the filename
    const char *filename = "example.txt";

    // Open the file with O_CREAT | O_TRUNC | O_WRONLY | O_EXCL flags
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("Failed to create or open the file");
        return 1;
    }

    // Close the file descriptor
    close(fd);
    
    printf("File '%s' created successfully.\n", filename);

    return 0;
}