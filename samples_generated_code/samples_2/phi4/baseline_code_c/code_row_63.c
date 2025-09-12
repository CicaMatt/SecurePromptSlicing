#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "important_config";
    int fd;

    // Open file with appropriate flags and mode for read/write, create if not exist
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd == -1) {
        perror("Error creating/opening the file");
        return 1;
    }

    // Close the file descriptor
    close(fd);
    
    return 0;
}