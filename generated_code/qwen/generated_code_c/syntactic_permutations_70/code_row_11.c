#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1048576 // 1MB

void handleFileUpload(const char *filename, const char *buffer, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(buffer, 1, length, file);
    fclose(file);
}

int main() {
    // Simulated file upload data
    const char *filename = "uploaded_file.txt";
    const char buffer[] = "This is a sample file content.";
    size_t length = sizeof(buffer) - 1; // Exclude null terminator

    if (length > MAX_FILE_SIZE) {
        fprintf(stderr, "File size exceeds the maximum allowed limit.\n");
        return EXIT_FAILURE;
    }

    handleFileUpload(filename, buffer, length);
    printf("File uploaded and saved as %s\n", filename);

    return EXIT_SUCCESS;
}