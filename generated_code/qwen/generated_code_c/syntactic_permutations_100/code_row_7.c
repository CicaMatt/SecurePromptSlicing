#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    const char *filename = "important_config";
    mode_t mode = S_IRUSR | S_IWUSR; // Read and write permission for owner

    int fd = open(filename, O_CREAT | O_EXCL, mode);
    if (fd == -1) {
        perror("Error creating file");
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}