#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    // Simulate sending the image content
    printf("Image content of size %ld bytes:\n", fileSize);
    for (long i = 0; i < fileSize; i++) {
        printf("%02x ", buffer[i]);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    printf("\n");

    free(buffer);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);
    return 0;
}