#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_FOLDER "uploads"

void create_uploads_folder() {
    if (mkdir(UPLOADS_FOLDER, 0755) == -1 && errno != 17) { // 17 is EEXIST
        perror("Failed to create uploads folder");
        exit(EXIT_FAILURE);
    }
}

void upload_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_FOLDER, filename);
    FILE *out = fopen(path, "wb");
    if (!out) {
        fclose(file);
        perror("Failed to create output file");
        return;
    }

    const int buffer_size = 1024;
    char buffer[buffer_size];
    size_t n;
    while ((n = fread(buffer, 1, buffer_size, file)) > 0) {
        fwrite(buffer, 1, n, out);
    }

    fclose(file);
    fclose(out);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    create_uploads_folder();
    upload_file(argv[1]);

    printf("File uploaded successfully.\n");
    return EXIT_SUCCESS;
}