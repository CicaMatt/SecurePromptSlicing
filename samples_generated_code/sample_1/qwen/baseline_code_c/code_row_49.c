#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* name) {
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "images/%s", name);

    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(filesize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, filesize, file);
    fclose(file);

    // Simulate sending response
    printf("Content-Length: %ld\r\n", filesize);
    printf("Content-Type: image/jpeg\r\n"); // Adjust MIME type as necessary
    printf("\r\n");
    fwrite(buffer, 1, filesize, stdout);

    free(buffer);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);
    return 0;
}