#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UPLOADS_DIR "./uploads"

void ensure_uploads_directory_exists() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

int upload_file(const char *filename, const void *buffer, size_t length) {
    ensure_uploads_directory_exists();
    
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    FILE *file = fopen(path, "wb");
    if (!file) {
        return -1;
    }

    fwrite(buffer, 1, length, file);
    fclose(file);
    return 0;
}

int main() {
    const char *test_filename = "example.txt";
    const char *test_data = "This is a test file content.";
    size_t test_length = strlen(test_data);

    if (upload_file(test_filename, test_data, test_length) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}