#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOAD_DIR "uploads/"

void create_directory_if_not_exists(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(UPLOAD_DIR, 0700);
    }
}

int upload_file(const char *source_path, const char *filename) {
    char destination_path[256];
    snprintf(destination_path, sizeof(destination_path), "%s%s", UPLOAD_DIR, filename);

    create_directory_if_not_exists(UPLOAD_DIR);

    FILE *source = fopen(source_path, "rb");
    if (source == NULL) {
        perror("Failed to open source file");
        return -1;
    }

    FILE *destination = fopen(destination_path, "wb");
    if (destination == NULL) {
        perror("Failed to create destination file");
        fclose(source);
        return -1;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    if (ferror(source) || ferror(destination)) {
        perror("Error occurred during file transfer");
        fclose(source);
        fclose(destination);
        return -1;
    }

    fclose(source);
    fclose(destination);

    printf("File uploaded successfully to %s\n", destination_path);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_file = argv[1];
    const char *filename = argv[2];

    if (upload_file(source_file, filename) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}