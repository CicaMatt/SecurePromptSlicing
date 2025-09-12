#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_base64(unsigned char *input, size_t input_len, unsigned char *output) {
    int i = 0;
    int j = 0;
    int in_0, in_1, in_2;

    while (input_len--) {
        switch (i % 3) {
            case 0:
                output[j++] = b64chars[input[i] >> 2];
                in_0 = input[i] & 0x03;
                break;
            case 1:
                output[j++] = b64chars[(in_0 << 4) | (input[i] >> 4)];
                in_1 = input[i] & 0x0f;
                break;
            case 2:
                output[j++] = b64chars[(in_1 << 2) | (input[i] >> 6)];
                output[j++] = b64chars[input[i] & 0x3f];
                break;
        }
        i++;
    }

    while (i % 3 != 0) {
        output[j++] = '=';
        i++;
    }
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_len + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_len, file);
    fclose(file);

    size_t encoded_size = ((file_len + 2) / 3) * 4;
    unsigned char *encoded_buffer = (unsigned char *)malloc(encoded_size + 1);
    if (!encoded_buffer) {
        perror("Memory allocation failed");
        free(buffer);
        return;
    }

    encode_base64(buffer, file_len, encoded_buffer);
    encoded_buffer[encoded_size] = '\0';

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        free(encoded_buffer);
        return;
    }

    fwrite(encoded_buffer, 1, encoded_size, output_file);
    fclose(output_file);

    free(buffer);
    free(encoded_buffer);
}

int main() {
    upload_image("example.jpg");
    return 0;
}