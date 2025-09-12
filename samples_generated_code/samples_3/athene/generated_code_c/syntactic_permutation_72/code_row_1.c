#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_FOLDER "uploads"

void create_uploads_folder() {
    if (mkdir(UPLOADS_FOLDER, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads folder");
        exit(EXIT_FAILURE);
    }
}

void upload_file(const char *filename) {
    FILE *source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open file");
        return;
    }

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", UPLOADS_FOLDER, filename);

    FILE *dest = fopen(dest_path, "wb");
    if (!dest) {
        perror("Failed to create destination file");
        fclose(source);
        return;
    }

    const int buffer_size = 1024;
    unsigned char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, source)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    fclose(source);
    fclose(dest);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    create_uploads_folder();
    upload_file(argv[1]);

    return EXIT_SUCCESS;
}