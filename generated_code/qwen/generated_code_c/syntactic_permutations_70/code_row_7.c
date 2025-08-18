#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1MB
#define UPLOADS_DIR "./uploads/"

void upload_file(FILE* file, const char* filename) {
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    FILE* dest = fopen(filepath, "wb");
    if (!dest) {
        perror("Failed to open destination file");
        return;
    }

    char buffer[MAX_FILE_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    fclose(dest);
}

int main() {
    FILE* uploaded_file = fopen("example_upload.txt", "rb"); // Simulate file upload
    if (!uploaded_file) {
        perror("Failed to open uploaded file");
        return EXIT_FAILURE;
    }

    upload_file(uploaded_file, "example_upload.txt");

    fclose(uploaded_file);
    return EXIT_SUCCESS;
}