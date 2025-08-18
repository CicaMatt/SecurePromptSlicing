#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int encode_base64(const unsigned char *input, size_t length, char **output);
void free_base64(char *b64);

void upload_image(const char *image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    char *encoded_image;
    int encoded_length = encode_base64(buffer, file_size, &encoded_image);
    free(buffer);

    if (encoded_length < 0) {
        fprintf(stderr, "Base64 encoding failed\n");
        return;
    }

    FILE *output_file = fopen("encoded_image.txt", "w");
    if (!output_file) {
        perror("Error opening output file");
        free_base64(encoded_image);
        return;
    }

    fwrite(encoded_image, 1, encoded_length, output_file);
    fclose(output_file);

    free_base64(encoded_image);
}

int encode_base64(const unsigned char *input, size_t length, char **output) {
    static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    *output = malloc((length + 2) / 3 * 4 + 1); // Allocate buffer for encoded string
    if (!*output) return -1;

    unsigned int i, j;
    unsigned char a3[3];
    unsigned char a4[4];

    for (i = 0, j = 0; length--) {
        a3[i++] = *(input++);
        if (i == 3) {
            a4[0] = (a3[0] & 0xfc) >> 2;
            a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
            a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
            a4[3] = (a3[2] & 0x3f);

            for (i = 0; i < 4; i++)
                *(*output + j++) = base64_table[a4[i]];
            i = 0;
        }
    }

    if (i) {
        for (; i < 3; i++)
            a3[i] = '\0';

        a4[0] = (a3[0] & 0xfc) >> 2;
        a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
        a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
        a4[3] = (a3[2] & 0x3f);

        for (i = 0; i < (length + 1) % 3 + 1; i++)
            *(*output + j++) = base64_table[a4[i]];

        while ((length + 1) % 3) {
            *(*output + j++) = '=';
        }
    }

    *(*output + j) = '\0';
    return j;
}

void free_base64(char *b64) {
    free(b64);
}