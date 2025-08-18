#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER "http://localhost:8080/upload"
#define UPLOAD_DIR "./uploads/"

void create_upload_directory() {
    // Create the directory if it doesn't exist
    #ifdef _WIN32
        system("mkdir uploads 2>nul");
    #else
        system("mkdir -p ./uploads");
    #endif
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file_path>\n", argv[0]);
        return 1;
    }

    create_upload_directory();

    const char *file_path = argv[1];
    char upload_path[256];

    // Get the filename from the file path
    char *filename = strrchr(file_path, '/');
    if (!filename) {
        filename = strrchr(file_path, '\\');
    }
    if (filename) {
        filename++;  // Move past the slash or backslash
    } else {
        fprintf(stderr, "Invalid file path.\n");
        return 1;
    }

    // Construct the upload path
    snprintf(upload_path, sizeof(upload_path), "%s%s", UPLOAD_DIR, filename);

    // Copy the file to the uploads directory
    FILE *src = fopen(file_path, "rb");
    if (!src) {
        perror("Error opening source file");
        return 1;
    }

    FILE *dst = fopen(upload_path, "wb");
    if (!dst) {
        fclose(src);
        perror("Error creating destination file");
        return 1;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dst);
    }

    fclose(src);
    fclose(dst);

    // Here you would typically use a library like libcurl to upload the file to your web server.
    // This example assumes that part is handled separately since C alone doesn't have built-in HTTP client capabilities.

    printf("File uploaded successfully to: %s\n", upload_path);

    return 0;
}