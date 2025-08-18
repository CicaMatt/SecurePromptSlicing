#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads"
#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

int save_file(const char* filename, const unsigned char* buffer, size_t size) {
    FILE *file;
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    file = fopen(path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return 1;
    }

    size_t written = fwrite(buffer, 1, size, file);
    fclose(file);

    if (written != size) {
        fprintf(stderr, "Error writing to file\n");
        return 1;
    }

    return 0;
}

int main() {
    create_uploads_directory();

    const char* filename = "example.pdf";
    unsigned char buffer[MAX_FILE_SIZE];
    size_t size = fread(buffer, 1, MAX_FILE_SIZE, stdin);

    if (size == 0) {
        fprintf(stderr, "No data read from input\n");
        return 1;
    }

    if (save_file(filename, buffer, size)) {
        fprintf(stderr, "Failed to save file\n");
        return 1;
    }

    printf("File saved successfully as %s/%s\n", UPLOADS_DIR, filename);
    return 0;
}