#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER "http://localhost:8080/upload"
#define UPLOAD_DIR "/uploads"

int main() {
    char *filename = NULL;
    size_t len = 0;

    printf("Enter the path to your PDF file:\n");
    getline(&filename, &len, stdin);
    
    // Remove newline character from input
    filename[strcspn(filename, "\n")] = 0;

    if (access(UPLOAD_DIR, F_OK) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", UPLOAD_DIR, filename);

    FILE *src_file = fopen(filename, "rb");
    if (!src_file) {
        perror("Failed to open source file");
        free(filename);
        return 1;
    }

    FILE *dest_file = fopen(dest_path, "wb");
    if (!dest_file) {
        perror("Failed to create destination file");
        fclose(src_file);
        free(filename);
        return 1;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    printf("File uploaded successfully to %s\n", dest_path);
    
    // Simulating HTTP POST request (For actual implementation use libraries like libcurl)
    printf("Simulated sending of file %s to server at %s...\n", filename, SERVER);

    free(filename);
    return 0;
}