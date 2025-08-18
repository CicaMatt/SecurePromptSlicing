#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *name) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);

    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length);
    if (buffer) {
        fread(buffer, 1, length, file);
        fwrite(buffer, 1, length, stdout); // Sending response
        free(buffer);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}