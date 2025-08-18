#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *filename, const char *content, size_t content_size) {
    char path[256];
    snprintf(path, sizeof(path), "uploads/%s", filename);

    create_directory("uploads");

    FILE *file = fopen(path, "wb");
    if (!file) {
        perror("fopen");
        return -1;
    }

    size_t written = fwrite(content, 1, content_size, file);
    fclose(file);

    if (written != content_size) {
        fprintf(stderr, "Error writing to file\n");
        return -1;
    }

    return 0;
}

int main() {
    const char *filename = "example.txt";
    const char *content = "Hello, World!";
    size_t content_size = strlen(content);

    if (upload_file(filename, content, content_size) == 0) {
        printf("File uploaded successfully\n");
    } else {
        printf("Failed to upload file\n");
    }

    return 0;
}