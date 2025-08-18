#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads"
#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

int upload_file(const char* file_path, const char* destination_name) {
    FILE *source_file = fopen(file_path, "rb");
    if (!source_file) {
        perror("Failed to open source file");
        return -1;
    }

    char destination_path[256];
    snprintf(destination_path, sizeof(destination_path), "%s/%s", UPLOADS_DIR, destination_name);

    FILE *destination_file = fopen(destination_path, "wb");
    if (!destination_file) {
        perror("Failed to create destination file");
        fclose(source_file);
        return -1;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
        if (ftell(destination_file) > MAX_FILE_SIZE) {
            fprintf(stderr, "File exceeds maximum allowed size\n");
            fclose(source_file);
            fclose(destination_file);
            remove(destination_path);
            return -1;
        }
    }

    fclose(source_file);
    fclose(destination_file);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source-file> <destination-name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    create_uploads_directory();
    if (upload_file(argv[1], argv[2]) == 0) {
        printf("File uploaded successfully\n");
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Failed to upload file\n");
        return EXIT_FAILURE;
    }
}