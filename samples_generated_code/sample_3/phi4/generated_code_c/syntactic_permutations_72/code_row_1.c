#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int save_file_to_directory(const char *filename, const char *upload_dir) {
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s/%s", upload_dir, filename);

    FILE *file = fopen(file_path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return 1;
    }

    // Simulate reading from stdin (or another source) and saving it
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
        if (fwrite(buffer, 1, bytes_read, file) != bytes_read) {
            perror("Failed to write data to file");
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    create_directory(upload_dir);
    
    if (save_file_to_directory(filename, upload_dir)) {
        fprintf(stderr, "Failed to save file: %s\n", filename);
    } else {
        printf("File uploaded successfully: %s\n", filename);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    upload_file(argv[1]);

    return 0;
}