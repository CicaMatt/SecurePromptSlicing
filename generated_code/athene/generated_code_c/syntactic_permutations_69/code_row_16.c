#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    static const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const int block_size = 3;
    const int encoded_block_size = 4;
    const int padding_character = '=';

    if (input_length == 0) return NULL;

    *output_length = ((input_length + 2) / 3) * 4;

    char *encoded_data = malloc(*output_length + 1);
    if (encoded_data == NULL) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = input_length % block_size; i > 0; i--) {
        encoded_data[*output_length - 1] = padding_character;
        (*output_length)--;
    }
    encoded_data[*output_length] = '\0';

    return encoded_data;
}

char *upload_image(const char *filename, size_t *encoded_len) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) return NULL;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    fread(buffer, 1, file_size, file);
    fclose(file);

    char *encoded_image = base64_encode(buffer, file_size, encoded_len);
    free(buffer);
    return encoded_image;
}

int main() {
    size_t encoded_length;
    char *encoded_image = upload_image("image.jpg", &encoded_length);
    if (encoded_image != NULL) {
        printf("Encoded image length: %zu\n", encoded_length);
        // Print or use the encoded image as needed
        free(encoded_image);
    } else {
        fprintf(stderr, "Failed to encode image.\n");
    }
    return 0;
}