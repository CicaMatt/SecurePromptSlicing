#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void upload_file(const char* filename, FILE* file) {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    FILE* dest_file = fopen(filepath, "wb");
    if (!dest_file) {
        perror("Failed to open destination file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > MAX_FILE_SIZE) {
        fprintf(stderr, "File size exceeds maximum allowed\n");
        fclose(dest_file);
        return;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(file);
    fclose(dest_file);

    printf("File uploaded successfully: %s\n", filepath);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <file_descriptor>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    int file_descriptor = atoi(argv[2]);

    FILE* file = fdopen(file_descriptor, "rb");
    if (!file) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    upload_file(filename, file);

    return EXIT_SUCCESS;
}