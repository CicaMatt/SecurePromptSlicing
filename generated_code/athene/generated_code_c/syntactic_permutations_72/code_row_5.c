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

void upload_file(const char *filename, const unsigned char *data, size_t length) {
    create_uploads_folder();

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_FOLDER, filename);

    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fwrite(data, 1, length, file);
    fclose(file);
}