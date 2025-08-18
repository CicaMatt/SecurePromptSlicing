#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encode data to base64
char* base64_encode(const unsigned char* input, int length) {
    static const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char *output = (char*)malloc((length + 2) / 3 * 4 + 1);
    if (!output) return NULL;

    int i, j;
    for (i = 0, j = 0; i < length;) {
        unsigned char octet_a = i < length ? input[i++] : 0;
        unsigned char octet_b = i < length ? input[i++] : 0;
        unsigned char octet_c = i < length ? input[i++] : 0;

        int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        output[j++] = b64chars[(triple >> 3 * 6) & 0x3F];
        output[j++] = b64chars[(triple >> 2 * 6) & 0x3F];
        output[j++] = (i < length + 2) ? b64chars[(triple >> 1 * 6) & 0x3F] : '=';
        output[j++] = (i < length + 1) ? b64chars[(triple >> 0 * 6) & 0x3F] : '=';
    }
    output[j] = '\0';

    return output;
}

void upload_image(const char* filename, const char* output_filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char*)malloc(file_size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    fclose(file);

    if (bytes_read != file_size) {
        perror("Failed to read file");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    char *base64_data = base64_encode(buffer, file_size);
    free(buffer);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(base64_data);
        exit(EXIT_FAILURE);
    }

    fprintf(output_file, "%s", base64_data);
    fclose(output_file);
    free(base64_data);
}

int main() {
    upload_image("image.png", "encoded_image.txt");
    return 0;
}