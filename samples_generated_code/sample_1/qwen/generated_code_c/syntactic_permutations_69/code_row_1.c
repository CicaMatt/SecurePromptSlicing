#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy implementation of base64 encoding for demonstration purposes
char* base64_encode(const unsigned char* data, size_t input_length) {
    static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char* output = (char*)malloc(input_length * 4 / 3 + 4);
    if (!output) return NULL;
    
    unsigned i = 0, j = 0;
    while (i < input_length) {
        unsigned octet_a = i < input_length ? data[i++] : 0;
        unsigned octet_b = i < input_length ? data[i++] : 0;
        unsigned octet_c = i < input_length ? data[i++] : 0;

        unsigned triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        output[j++] = b64[(triple >> 3 * 6) & 0x3F];
        output[j++] = b64[(triple >> 2 * 6) & 0x3F];
        output[j++] = (i < input_length + 2) ? b64[(triple >> 1 * 6) & 0x3F] : '=';
        output[j++] = (i < input_length + 1) ? b64[(triple >> 0 * 6) & 0x3F] : '=';
    }
    output[j] = '\0';
    return output;
}

void upload_image(const char* image_path, const char* output_file_path) {
    FILE* file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(file_size);
    if (!buffer) {
        fclose(file);
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    size_t read_bytes = fread(buffer, 1, file_size, file);
    fclose(file);

    if (read_bytes != file_size) {
        free(buffer);
        perror("Failed to read file");
        exit(EXIT_FAILURE);
    }

    char* base64_image = base64_encode(buffer, file_size);
    free(buffer);

    FILE* output_file = fopen(output_file_path, "w");
    if (!output_file) {
        free(base64_image);
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    fprintf(output_file, "%s", base64_image);
    fclose(output_file);
    free(base64_image);
}

int main() {
    upload_image("input.jpg", "output.txt");
    return 0;
}