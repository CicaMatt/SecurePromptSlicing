#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOAD_DIR "uploads/"
#define MAX_FILE_NAME 1024

int main(int argc, char *argv[]) {
    FILE *source_file, *destination_file;
    char file_path[MAX_FILE_NAME];
    char buffer[1024];
    size_t bytes_read;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_to_upload>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    snprintf(file_path, MAX_FILE_NAME, "%s%s", UPLOAD_DIR, argv[1]);

    source_file = fopen(argv[1], "rb");
    if (!source_file) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    destination_file = fopen(file_path, "wb");
    if (!destination_file) {
        perror("Failed to create destination file");
        fclose(source_file);
        return EXIT_FAILURE;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);

    printf("File uploaded successfully to %s\n", file_path);
    return EXIT_SUCCESS;
}