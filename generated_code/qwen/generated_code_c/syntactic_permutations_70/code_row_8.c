#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads"
#define MAX_FILENAME_LENGTH 256

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

int upload_file(const char *filename, const char *content) {
    char path[MAX_FILENAME_LENGTH];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    FILE *file = fopen(path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return 1;
    }

    size_t content_length = strlen(content);
    if (fwrite(content, 1, content_length, file) != content_length) {
        perror("Failed to write to file");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

int main() {
    create_uploads_directory();

    const char *filename = "example.txt";
    const char *content = "This is an example file content.";

    if (upload_file(filename, content) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}