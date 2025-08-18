#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOAD_DIR "uploads/"

typedef struct {
    char *data;
    size_t size;
} File;

void save_file(const char *path, const File *file) {
    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    fwrite(file->data, 1, file->size, fp);
    fclose(fp);
}

void upload_file(const File *file, const char *filename) {
    char path[256];
    snprintf(path, sizeof(path), "%s%s", UPLOAD_DIR, filename);
    save_file(path, file);
}

int main() {
    // Example usage
    const char sample_data[] = "This is a test file content.";
    File myFile = { .data = (char *)sample_data, .size = strlen(sample_data) };
    upload_file(&myFile, "testfile.txt");
    return 0;
}