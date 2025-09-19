#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void save_file(const char* filename, const unsigned char* content, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fwrite(content, 1, length, file);
    fclose(file);
}

int handle_file_upload(const char* filename, const unsigned char* content, size_t length) {
    if (length > MAX_FILE_SIZE) {
        fprintf(stderr, "File too large\n");
        return -1;
    }

    save_file(filename, content, length);

    printf("File saved successfully: %s\n", filename);
    return 0;
}

int main() {
    const char* test_filename = "test.txt";
    unsigned char test_content[] = "This is a test file content.";
    size_t test_length = sizeof(test_content) - 1; // Exclude null terminator

    return handle_file_upload(test_filename, test_content, test_length);
}