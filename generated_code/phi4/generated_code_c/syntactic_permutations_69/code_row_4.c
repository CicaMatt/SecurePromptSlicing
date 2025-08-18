#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Base64 encoding table
static const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Function prototypes
void upload_image(const char *filename);
size_t base64_encode(const unsigned char *input, size_t length, char *output);
int read_file_to_buffer(const char *filename, unsigned char **buffer, size_t *length);

void upload_image(const char *filename) {
    unsigned char *file_data = NULL;
    size_t file_length = 0;

    if (read_file_to_buffer(filename, &file_data, &file_length)) {
        char *encoded_str = malloc((4 * ((file_length + 2) / 3)) + 1);
        if (!encoded_str) {
            fprintf(stderr, "Memory allocation failed\n");
            free(file_data);
            return;
        }

        size_t encoded_length = base64_encode(file_data, file_length, encoded_str);

        // Write the encoded string to a new file
        FILE *output_file = fopen("encoded_image.txt", "w");
        if (output_file) {
            fwrite(encoded_str, 1, encoded_length, output_file);
            fclose(output_file);
        } else {
            fprintf(stderr, "Failed to open output file\n");
        }

        free(encoded_str);
    }
    free(file_data);
}

size_t base64_encode(const unsigned char *input, size_t length, char *output) {
    if (!input || !length || !output)
        return 0;

    size_t i = 0;
    size_t j = 0;
    size_t encoded_length = 4 * ((length + 2) / 3);

    while (length--) {
        unsigned char octet_a = input[i++];
        unsigned char octet_b = i < length ? input[i] : 0;
        unsigned char octet_c = i < length + 1 ? input[i] : 0;

        output[j++] = encoding_table[(octet_a & 0xFC) >> 2];
        output[j++] = encoding_table[((octet_a & 0x03) << 4) | ((octet_b & 0xF0) >> 4)];
        output[j++] = i < length + 1 ? encoding_table[((octet_b & 0x0F) << 2) | ((octet_c & 0xC0) >> 6)] : '=';
        output[j++] = i >= length + 1 ? '=' : encoding_table[octet_c & 0x3F];
    }

    return encoded_length;
}

int read_file_to_buffer(const char *filename, unsigned char **buffer, size_t *length) {
    FILE *file = fopen(filename, "rb");
    if (!file)
        return -1;

    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    *buffer = malloc(*length);
    if (!*buffer) {
        fclose(file);
        return -1;
    }

    fread(*buffer, 1, *length, file);
    fclose(file);

    return 0;
}

int main() {
    const char *filename = "example_image.jpg"; // Replace with the path to your image
    upload_image(filename);
    return 0;
}