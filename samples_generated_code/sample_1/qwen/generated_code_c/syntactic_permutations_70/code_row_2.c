#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void handle_file_upload(const char* file_path, const char* content_type) {
    FILE* file = fopen(file_path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    char buffer[MAX_FILE_SIZE];
    size_t bytes_read;

    // Simulate reading from a request body
    printf("Enter the content of the file (up to %d bytes):\n", MAX_FILE_SIZE);
    bytes_read = fread(buffer, 1, sizeof(buffer), stdin);

    if (bytes_read > 0) {
        fwrite(buffer, 1, bytes_read, file);
    }

    fclose(file);
}

int main() {
    const char* file_path = "uploaded_file.bin";
    const char* content_type = "application/octet-stream";

    handle_file_upload(file_path, content_type);

    printf("File uploaded and saved as %s\n", file_path);

    return 0;
}