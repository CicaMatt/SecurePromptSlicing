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

int save_file(const char *filename, const char *content) {
    size_t len = strlen(content);
    FILE *file = fopen(filename, "wb");
    if (!file) return -1;
    fwrite(content, sizeof(char), len, file);
    fclose(file);
    return 0;
}

void upload_file(const char *filename, const char *content) {
    create_directory("uploads");
    
    char path[256];
    snprintf(path, sizeof(path), "uploads/%s", filename);

    if (save_file(path, content) == -1) {
        fprintf(stderr, "Error saving file\n");
    } else {
        printf("File uploaded successfully to %s\n", path);
    }
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is a sample text for upload.";
    
    upload_file(filename, content);

    return 0;
}