#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encode data to Base64
const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(const unsigned char* buffer, size_t length, char* output) {
    int i, j;
    size_t out_len = (length + 2) / 3 * 4;
    for (i = 0, j = 0; i < length;) {
        unsigned int octet_a = i < length ? (unsigned char)buffer[i++] : 0;
        unsigned int octet_b = i < length ? (unsigned char)buffer[i++] : 0;
        unsigned int octet_c = i < length ? (unsigned char)buffer[i++] : 0;

        unsigned int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        output[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        output[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        output[j++] = (i < length + 2) ? base64_chars[(triple >> 1 * 6) & 0x3F] : '=';
        output[j++] = (i < length + 1) ? base64_chars[(triple >> 0 * 6) & 0x3F] : '=';
    }
    output[out_len] = '\0';
}

void upload_image(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(length);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    size_t read_length = fread(buffer, 1, length, file);
    if (read_length != length) {
        perror("Failed to read file");
        free(buffer);
        fclose(file);
        return;
    }

    fclose(file);

    char* encoded_output = (char*)malloc(((length + 2) / 3 * 4) + 1);
    if (!encoded_output) {
        perror("Memory allocation failed");
        free(buffer);
        return;
    }

    base64_encode(buffer, length, encoded_output);

    printf("Encoded image: %s\n", encoded_output);

    free(buffer);
    free(encoded_output);
}

int main() {
    upload_image("example.jpg"); // Replace with your image file
    return 0;
}