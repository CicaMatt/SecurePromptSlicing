#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_uploads_directory() {
    struct stat st = {0};
    if (stat("uploads", &st) == -1) {
        mkdir("uploads", 0700);
    }
}

int upload_file(const char *filename) {
    FILE *source_file, *destination_file;
    char source_path[256];
    char destination_path[256];

    snprintf(source_path, sizeof(source_path), "%s", filename);

    create_uploads_directory();
    snprintf(destination_path, sizeof(destination_path), "uploads/%s", filename);

    source_file = fopen(source_path, "rb");
    if (!source_file) {
        perror("Failed to open file for reading");
        return 1;
    }

    destination_file = fopen(destination_path, "wb");
    if (!destination_file) {
        fclose(source_file);
        perror("Failed to open file for writing");
        return 1;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        if (fwrite(buffer, 1, bytes_read, destination_file) != bytes_read) {
            fclose(source_file);
            fclose(destination_file);
            perror("Failed to write file");
            return 1;
        }
    }

    fclose(source_file);
    fclose(destination_file);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    int result = upload_file(argv[1]);

    if (result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return result;
}