#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOAD_DIR "uploads/"
#define MAX_FILENAME_SIZE 256

void upload_file(const char *filename, const char *content, size_t content_length) {
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0700);
    }

    char filepath[MAX_FILENAME_SIZE];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(content, 1, content_length, file);
    fclose(file);
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is an example file content.";
    size_t content_length = strlen(content);

    upload_file(filename, content, content_length);

    return 0;
}