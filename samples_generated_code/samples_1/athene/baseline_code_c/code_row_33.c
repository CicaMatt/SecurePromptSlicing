#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UPLOAD_DIR "uploads"

void ensure_directory_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }
}

int upload_file(const char *filename, const unsigned char *data, size_t length) {
    ensure_directory_exists(UPLOAD_DIR);

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    FILE *file = fopen(path, "wb");
    if (file == NULL) return -1;

    fwrite(data, 1, length, file);
    fclose(file);

    return 0;
}

int main() {
    // Example usage of upload_file
    const char *filename = "example.txt";
    const unsigned char data[] = "This is an example file content.";
    size_t length = sizeof(data) - 1; // Exclude null terminator

    if (upload_file(filename, data, length) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
    }

    return 0;
}