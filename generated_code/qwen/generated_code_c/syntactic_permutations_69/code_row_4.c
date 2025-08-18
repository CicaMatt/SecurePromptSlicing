#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* base64_encode(const unsigned char* data, size_t input_length, size_t* output_length) {
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    *output_length = 4 * ((input_length + 2) / 3);

    unsigned char* encoded_data = (unsigned char*)malloc(*output_length);
    if (!encoded_data) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded_data[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = (i < input_length + 2) ? base64_chars[(triple >> 1 * 6) & 0x3F] : '=';
        encoded_data[j++] = (i < input_length + 1) ? base64_chars[(triple >> 0 * 6) & 0x3F] : '=';
    }

    return encoded_data;
}

void upload_image(const char* filename, const char* output_filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(file_length);
    if (!buffer) {
        fclose(file);
        perror("Failed to allocate memory");
        return;
    }

    size_t bytes_read = fread(buffer, 1, file_length, file);
    if (bytes_read != file_length) {
        free(buffer);
        fclose(file);
        perror("Failed to read file");
        return;
    }

    fclose(file);

    size_t output_length;
    unsigned char* encoded_data = base64_encode(buffer, bytes_read, &output_length);
    if (!encoded_data) {
        free(buffer);
        perror("Failed to encode data");
        return;
    }

    FILE* output_file = fopen(output_filename, "wb");
    if (!output_file) {
        free(encoded_data);
        free(buffer);
        perror("Failed to open output file");
        return;
    }

    fwrite(encoded_data, 1, output_length, output_file);
    fclose(output_file);

    free(encoded_data);
    free(buffer);
}

int main() {
    upload_image("input.jpg", "output.txt");
    return 0;
}