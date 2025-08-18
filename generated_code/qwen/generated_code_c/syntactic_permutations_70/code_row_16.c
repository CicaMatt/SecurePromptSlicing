#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1MB
#define UPLOAD_DIR "./uploads/"

void handle_upload(const char* filename, const char* content, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(content, 1, length, file);
    fclose(file);
}

void upload_file(const char* filename, const char* content, size_t length) {
    if (length > MAX_FILE_SIZE) {
        fprintf(stderr, "File too large\n");
        return;
    }

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", UPLOAD_DIR, filename);

    handle_upload(full_path, content, length);
}

int main() {
    // Example usage
    const char* example_filename = "example.txt";
    const char* example_content = "This is an example file content.";
    size_t example_length = strlen(example_content);

    upload_file(example_filename, example_content, example_length);

    return 0;
}