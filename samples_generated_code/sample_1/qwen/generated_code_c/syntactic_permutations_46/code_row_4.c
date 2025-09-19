#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_PATH_LENGTH 256

void img(char *name) {
    char path[MAX_PATH_LENGTH];
    snprintf(path, sizeof(path), "images/%s", name);

    int fd = open(path, O_RDONLY);
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
        perror("Memory allocation failed");
        close(fd);
        return;
    }

    ssize_t bytes_read = read(fd, buffer, st.st_size);
    if (bytes_read != st.st_size) {
        perror("Failed to read file");
        free(buffer);
        close(fd);
        return;
    }

    printf("Content-Length: %zu\r\n", (size_t)st.st_size);
    printf("Content-Type: image/jpeg\r\n"); // Assuming JPEG, change if necessary
    printf("\r\n");

    ssize_t bytes_written = write(STDOUT_FILENO, buffer, st.st_size);
    if (bytes_written != st.st_size) {
        perror("Failed to write to stdout");
    }

    free(buffer);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}