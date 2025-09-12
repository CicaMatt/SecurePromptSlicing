#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encode_base64(const unsigned char *input, size_t length, char **output) {
    static const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i, j;
    size_t output_size = 4 * ((length + 2) / 3);
    *output = malloc(output_size + 1);
    if (*output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    memset(*output, 0, output_size + 1);
    for (i = 0, j = 0; i < length;) {
        uint32_t octet_a = i < length ? (unsigned char)input[i++] : 0;
        uint32_t octet_b = i < length ? (unsigned char)input[i++] : 0;
        uint32_t octet_c = i < length ? (unsigned char)input[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        ((*output)[j++] = encoding_table[(triple >> 3 * 6) & 0x3F]);
        ((*output)[j++] = encoding_table[(triple >> 2 * 6) & 0x3F]);
        ((*output)[j++] = encoding_table[(triple >> 1 * 6) & 0x3F]);
        ((*output)[j++] = encoding_table[(triple >> 0 * 6) & 0x3F]);
    }
    for (i = length; i % 3; i++)
        (*output)[--j] = '=';
}

void write_base64_to_file(const char *base64, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        exit(1);
    }
    fprintf(file, "%s", base64);
    fclose(file);
}

void upload_image(const char *image_path, const char *output_file) {
    FILE *image = fopen(image_path, "rb");
    if (!image) {
        perror("Failed to open image file");
        exit(1);
    }

    fseek(image, 0, SEEK_END);
    long length = ftell(image);
    fseek(image, 0, SEEK_SET);

    unsigned char *buffer = malloc(length);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(image);
        exit(1);
    }
    fread(buffer, 1, length, image);
    fclose(image);

    char *encoded_image;
    encode_base64(buffer, length, &encoded_image);
    free(buffer);

    write_base64_to_file(encoded_image, output_file);
    free(encoded_image);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_path> <output_file>\n", argv[0]);
        return 1;
    }
    upload_image(argv[1], argv[2]);
    return 0;
}