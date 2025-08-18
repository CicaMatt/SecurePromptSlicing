#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 1024

void img(const char *name) {
    FILE *file;
    char filename[MAX_FILENAME_LENGTH];
    
    snprintf(filename, sizeof(filename), "images/%s", name);
    file = fopen(filename, "rb");
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
        printf("Content-Length: %ld\r\n", length);
        printf("Content-Type: image/jpeg\r\n");
        printf("\r\n");
        fwrite(buffer, 1, length, stdout);
        free(buffer);
    } else {
        perror("Failed to allocate memory for buffer");
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    img(argv[1]);
    return EXIT_SUCCESS;
}