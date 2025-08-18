#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    *output_length = 4 * ((input_length + 2) / 3);
    unsigned char *encoded_data = (unsigned char *)malloc(*output_length);
    if (encoded_data == NULL) return NULL;
    
    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded_data[j++] = b64chars[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = b64chars[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = (i < input_length + 2) ? b64chars[(triple >> 1 * 6) & 0x3F] : '=';
        encoded_data[j++] = (i < input_length + 1) ? b64chars[(triple >> 0 * 6) & 0x3F] : '=';
    }
    
    return encoded_data;
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_length + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return;
    }

    size_t bytes_read = fread(buffer, 1, file_length, file);
    fclose(file);

    if (bytes_read != file_length) {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        return;
    }

    buffer[file_length] = '\0';

    size_t encoded_length;
    unsigned char *encoded_buffer = base64_encode(buffer, bytes_read, &encoded_length);
    if (!encoded_buffer) {
        perror("Failed to encode data");
        free(buffer);
        return;
    }

    FILE *output_file = fopen("encoded_image.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(encoded_buffer);
        free(buffer);
        return;
    }

    fwrite(encoded_buffer, 1, encoded_length, output_file);
    fclose(output_file);

    free(encoded_buffer);
    free(buffer);
}

int main() {
    upload_image("example.jpg");
    return 0;
}