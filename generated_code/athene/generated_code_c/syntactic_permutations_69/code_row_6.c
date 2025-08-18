#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    static const char encode_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    if (input_length == 0) return NULL;

    *output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(*output_length + 1);
    if (!encoded_data) return NULL;
    memset(encoded_data, '=', *output_length);

    size_t i, j;
    for (i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encode_chars[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encode_chars[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encode_chars[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encode_chars[(triple >> 0 * 6) & 0x3F];
    }

    encoded_data[*output_length] = '\0';
    return encoded_data;
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *data = malloc(file_length);
    if (fread(data, 1, file_length, file) != file_length) {
        perror("Failed to read file");
        fclose(file);
        free(data);
        exit(EXIT_FAILURE);
    }
    fclose(file);

    size_t encoded_length;
    char *encoded_data = base64_encode(data, file_length, &encoded_length);
    if (!encoded_data) {
        fprintf(stderr, "Base64 encoding failed\n");
        free(data);
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen("encoded_image.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(encoded_data);
        free(data);
        exit(EXIT_FAILURE);
    }
    fprintf(output_file, "%s\n", encoded_data);

    fclose(output_file);
    free(encoded_data);
    free(data);
}