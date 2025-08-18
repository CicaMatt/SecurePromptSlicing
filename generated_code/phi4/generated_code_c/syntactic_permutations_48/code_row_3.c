#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void img(const char *file_path) {
    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Failed to get file stats");
        close(fd);
        return;
    }

    char *buffer = malloc(st.st_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        close(fd);
        return;
    }

    ssize_t bytes_read = read(fd, buffer, st.st_size);
    if (bytes_read == -1) {
        perror("Failed to read file");
        free(buffer);
        close(fd);
        return;
    }
    
    // Here you would normally send the data over a network
    printf("%s\n", buffer);  // For demonstration purposes

    free(buffer);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}