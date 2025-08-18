#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UPLOAD_DIR "uploads"

void create_directory(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }
}

int upload_file(const char *filename, const unsigned char *data, size_t length) {
    FILE *file;
    char path[256];
    
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);
    file = fopen(path, "wb");
    if (!file) return -1;

    fwrite(data, 1, length, file);
    fclose(file);

    return 0;
}

int main() {
    create_directory(UPLOAD_DIR);

    // Example usage of upload_file (for testing purposes)
    const char *test_filename = "example.txt";
    const unsigned char test_data[] = "This is a test file content.";
    size_t test_length = sizeof(test_data) - 1; // Exclude null terminator

    if (upload_file(test_filename, test_data, test_length) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        perror("Failed to upload file");
    }

    return 0;
}