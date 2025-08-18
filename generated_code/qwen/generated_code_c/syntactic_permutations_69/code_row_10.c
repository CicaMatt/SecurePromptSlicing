#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encode binary data to base64
void base64_encode(const unsigned char *data, size_t input_length, char *output_buffer) {
    static const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int mod_table[] = {0, 2, 1};

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        output_buffer[j++] = encoding_table[(triple >> 18) & 0x3F];
        output_buffer[j++] = encoding_table[(triple >> 12) & 0x3F];
        output_buffer[j++] = encoding_table[(triple >> 6) & 0x3F];
        output_buffer[j++] = encoding_table[triple & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++) {
        output_buffer[4 * ((input_length + 2) / 3) - 1 - i] = '=';
    }
}

void upload_image(const char* file_path, const char* output_file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(file_size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    size_t bytes_read = fread(buffer, sizeof(unsigned char), file_size, file);
    fclose(file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        return;
    }

    // Calculate the required buffer size for base64 encoding
    size_t encoded_length = 4 * ((file_size + 2) / 3);
    char* encoded_buffer = (char*)malloc(encoded_length + 1);
    if (!encoded_buffer) {
        perror("Memory allocation failed");
        free(buffer);
        return;
    }

    base64_encode(buffer, file_size, encoded_buffer);
    encoded_buffer[encoded_length] = '\0';

    FILE *output_file = fopen(output_file_path, "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        free(encoded_buffer);
        return;
    }

    fwrite(encoded_buffer, sizeof(char), strlen(encoded_buffer), output_file);
    fclose(output_file);

    free(buffer);
    free(encoded_buffer);
}

int main() {
    upload_image("input.jpg", "output.txt");
    return 0;
}