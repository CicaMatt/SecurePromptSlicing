#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encode_base64(const unsigned char *input, size_t length, char **output) {
    const char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t output_len = 4 * ((length + 2) / 3);
    *output = malloc(output_len + 1);
    if (*output == NULL) exit(1);
    memset(*output, 0, output_len + 1);

    for (size_t i = 0, j = 0; i < length;) {
        uint32_t octet_a = i < length ? (unsigned char)input[i++] : 0;
        uint32_t octet_b = i < length ? (unsigned char)input[i++] : 0;
        uint32_t octet_c = i < length ? (unsigned char)input[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        (*output)[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        (*output)[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        (*output)[j++] = (i <= length + 1) ? base64_chars[(triple >> 1 * 6) & 0x3F] : '=';
        (*output)[j++] = (i < length + 2) ? base64_chars[(triple >> 0 * 6) & 0x3F] : '=';
    }
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(length);
    if (fread(buffer, 1, length, file) != length) {
        fclose(file);
        free(buffer);
        perror("Failed to read file");
        exit(1);
    }
    fclose(file);

    char *encoded;
    encode_base64(buffer, length, &encoded);
    free(buffer);

    FILE *out = fopen("output.b64", "w");
    if (!out) {
        free(encoded);
        perror("Failed to open output file");
        exit(1);
    }

    fprintf(out, "%s", encoded);
    fclose(out);
    free(encoded);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }
    upload_image(argv[1]);
    return 0;
}