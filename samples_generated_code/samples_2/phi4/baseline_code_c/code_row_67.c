#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *filename) {
    const char *upload_dir = "./uploads";
    create_directory(upload_dir);

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", upload_dir, filename);

    FILE *file = fopen(full_path, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return -1;
    }

    // Simulate reading data from a source and writing it to the file
    const char *data = "Sample content of the file.";
    size_t len = strlen(data);

    if (fwrite(data, 1, len, file) < len) {
        perror("Failed to write data to file");
        fclose(file);
        return -1;
    }

    fclose(file);
    printf("File uploaded successfully: %s\n", full_path);
    return 0;
}

int main() {
    const char *filename = "example.txt";
    if (upload_file(filename) != 0) {
        fprintf(stderr, "Error uploading file.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}