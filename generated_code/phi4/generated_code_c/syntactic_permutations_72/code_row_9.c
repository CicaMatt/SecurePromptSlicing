#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    char full_path[256];

    create_directory(upload_dir);

    snprintf(full_path, sizeof(full_path), "%s/%s", upload_dir, filename);

    FILE *file = fopen(full_path, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return -1;
    }

    // Simulate reading from an input source, e.g., stdin or a buffer
    char buffer[1024];
    size_t bytes_read;
    
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
        if (fwrite(buffer, 1, bytes_read, file) != bytes_read) {
            perror("Failed to write data to file");
            fclose(file);
            return -1;
        }
    }

    if (ferror(stdin)) {
        perror("Error reading input source");
        fclose(file);
        return -1;
    }

    fclose(file);

    printf("File uploaded successfully: %s\n", full_path);
    return 0;
}

int main() {
    const char *filename = "uploaded_file.txt";
    
    if (upload_file(filename) != 0) {
        fprintf(stderr, "Error uploading file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}