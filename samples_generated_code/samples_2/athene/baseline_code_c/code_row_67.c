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
        fclose(source);
        perror("Failed to create destination file");
        return;
    }

    char buffer[1024];
    size_t read;

    while ((read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, read, dest);
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