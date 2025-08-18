#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 1024

void img(const char* name) {
    char filename[MAX_FILENAME];
    snprintf(filename, sizeof(filename), "images/%s", name);

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long filelen = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(filelen + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, filelen, 1, file);
    fclose(file);

    printf("Content-Length: %ld\r\n", filelen);
    printf("Content-Type: image/jpeg\r\n"); // Assuming the image is a JPEG
    printf("\r\n");

    fwrite(buffer, filelen, 1, stdout);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}