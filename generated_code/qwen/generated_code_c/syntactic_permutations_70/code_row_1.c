#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads"
#define MAX_FILE_SIZE 1024 * 1024 // 1MB

int create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
    return 0;
}

void upload_file(const char *file_content, size_t file_size, const char *filename) {
    create_uploads_directory();

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOADS_DIR, filename);

    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    size_t written = fwrite(file_content, 1, file_size, fp);
    if (written != file_size) {
        fprintf(stderr, "Error writing to file\n");
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    // Example usage
    const char *file_content = "Example file content";
    size_t file_size = strlen(file_content);
    const char *filename = "example.txt";

    upload_file(file_content, file_size, filename);

    return 0;
}