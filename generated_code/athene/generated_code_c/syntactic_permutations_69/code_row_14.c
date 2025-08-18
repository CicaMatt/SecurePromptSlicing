#include <stdio.h>
#include <stdlib.h>

void encode_image(const unsigned char *data, size_t length, FILE *out) {
    for (size_t i = 0; i < length; i++) {
        fprintf(out, "%02X", data[i]);
    }
}

void upload_image(const char *filename) {
    FILE *in = fopen(filename, "rb");
    if (!in) {
        perror("Failed to open image file");
        exit(1);
    }

    fseek(in, 0, SEEK_END);
    long length = ftell(in);
    fseek(in, 0, SEEK_SET);

    unsigned char *buffer = malloc(length);
    if (fread(buffer, 1, length, in) != length) {
        perror("Failed to read image file");
        fclose(in);
        free(buffer);
        exit(1);
    }

    fclose(in);

    FILE *out = fopen("encoded_image.txt", "w");
    if (!out) {
        perror("Failed to open output file");
        free(buffer);
        exit(1);
    }

    encode_image(buffer, length, out);

    fclose(out);
    free(buffer);
}