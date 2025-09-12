#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_FOLDER "uploads"

void create_directory(const char *path) {
    mkdir(path, 0755);
}

int upload_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return -1;

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_FOLDER, filename);

    create_directory(UPLOADS_FOLDER);

    FILE *output = fopen(path, "wb");
    if (!output) {
        fclose(file);
        return -1;
    }

    char buffer[4096];
    size_t read_bytes;

    while ((read_bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, read_bytes, output);
    }

    fclose(file);
    fclose(output);

    return 0;
}