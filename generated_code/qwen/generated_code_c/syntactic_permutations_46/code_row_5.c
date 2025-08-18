#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH 1024

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);

    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, size, file);
    fclose(file);

    printf("Content-Length: %ld\r\n", size);
    printf("Content-Type: image/jpeg\r\n"); // Assuming JPEG for simplicity
    printf("\r\n");

    fwrite(buffer, 1, size, stdout);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}