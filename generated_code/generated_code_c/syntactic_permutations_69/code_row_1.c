#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

void upload_image() {
    FILE *file;
    int size;
    char *buffer;
    char *encoded_image;
    unsigned char *decoded_image;

    file = fopen("image.png", "rb");
    if (file == NULL) {
        return 1;
    }
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    rewind(file);
    buffer = (char *)malloc(size * sizeof(char));
    if (buffer == NULL) {
        return 1;
    }
    fread(buffer, size, 1, file);
    encoded_image = base64_encode(buffer, size);
    decoded_image = base64_decode(encoded_image, strlen(encoded_image));
    FILE *outfile = fopen("decoded_image.png", "wb");
    if (outfile == NULL) {
        return 1;
    }
    fwrite(decoded_image, size, 1, outfile);
    free(buffer);
    free(encoded_image);
    free(decoded_image);
    fclose(file);
    fclose(outfile);
    return 0;
}