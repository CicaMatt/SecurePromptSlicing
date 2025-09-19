#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "./uploads/"
#define BUFFER_SIZE 1024

int save_file(const char *filename, const unsigned char *buffer, size_t buffer_len) {
    char path[256];
    snprintf(path, sizeof(path), "%s%s", UPLOAD_DIR, filename);

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to create file");
        return -1;
    }

    ssize_t written = write(fd, buffer, buffer_len);
    if (written != (ssize_t)buffer_len) {
        close(fd);
        unlink(path);
        perror("Failed to write file");
        return -1;
    }

    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    struct stat st;
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t read_bytes;
    while ((read_bytes = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (save_file(filename, buffer, read_bytes) == -1) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    printf("File saved to %s\n", UPLOAD_DIR);
    return 0;
}