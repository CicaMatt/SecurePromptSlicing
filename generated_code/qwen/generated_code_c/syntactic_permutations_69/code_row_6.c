#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *encode_base64(const unsigned char *input, int input_length) {
    int output_length = 4 * ((input_length + 2) / 3);
    char *output = (char *)malloc(output_length + 1);
    if (!output) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        unsigned int octet_a = i < input_length ? (unsigned char)input[i++] : 0;
        unsigned int octet_b = i < input_length ? (unsigned char)input[i++] : 0;
        unsigned int octet_c = i < input_length ? (unsigned char)input[i++] : 0;

        unsigned int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        output[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        output[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        output[j++] = (i - input_length == 1) ? '=' : base64_chars[(triple >> 1 * 6) & 0x3F];
        output[j++] = (i - input_length > 1) ? '=' : base64_chars[(triple >> 0 * 6) & 0x3F];
    }
    output[output_length] = '\0';
    return output;
}

void upload_image(const char* filename, const char* output_filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(length);
    if (!buffer) {
        fclose(file);
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, length, file);
    fclose(file);

    char *encoded_image = encode_base64(buffer, length);
    free(buffer);

    if (!encoded_image) {
        perror("Failed to encode image");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        free(encoded_image);
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    fprintf(output_file, "%s", encoded_image);
    fclose(output_file);
    free(encoded_image);
}

int main() {
    upload_image("image.png", "encoded_image.txt");
    return 0;
}