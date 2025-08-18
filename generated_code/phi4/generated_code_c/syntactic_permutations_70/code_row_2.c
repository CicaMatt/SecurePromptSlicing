#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
    return 0;
}

void upload_file(const char *filename, const char *content, size_t length) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);

    FILE *file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fwrite(content, 1, length, file);
    fclose(file);
}

int main() {
    create_directory("uploads");

    const char *filename = "test.txt";
    const char *content = "Hello, this is a test file upload!";
    size_t content_length = strlen(content);

    upload_file(filename, content, content_length);

    printf("File uploaded successfully\n");
    
    return 0;
}