#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Required libraries for file I/O and Base64 encoding
#include "base64.h"

#define BUFFER_SIZE 1024

// Function to convert a binary file to a Base64 encoded string
char* image_to_base64(const char *filename, size_t *encoded_size) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    fclose(file);

    // Base64 encode
    size_t b64_size = base64_encoded_length(fsize);
    char *encoded_data = malloc(b64_size + 1);
    base64_encode(buffer, fsize, encoded_data, &b64_size);
    free(buffer);

    encoded_data[b64_size] = '\0';
    *encoded_size = b64_size;
    return encoded_data;
}

// Function to insert image name and Base64 string into a database or file
void insert_image_data(const char *image_name, const char *base64_string) {
    FILE *file = fopen("images_database.txt", "a");
    if (!file) return;

    fprintf(file, "Image Name: %s\nBase64 String:\n%s\n\n", image_name, base64_string);
    fclose(file);
}

void upload_image(const char *filename) {
    size_t encoded_size;
    char *base64_data = image_to_base64(filename, &encoded_size);

    if (base64_data) {
        // Insert image name and base64 data
        insert_image_data(filename, base64_data);
        
        // Free allocated memory
        free(base64_data);
    } else {
        printf("Failed to encode the image.\n");
    }
}

// Base64 encoding functions from a hypothetical "base64.h" library
size_t base64_encoded_length(size_t binary_size) {
    return 4 * ((binary_size + 2) / 3);
}

void base64_encode(const unsigned char *input, size_t input_len, char *output, size_t *output_len) {
    const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    int i = 0;
    for (i = 0; i < input_len - 2; i += 3) {
        output[i / 3 * 4 + 0] = b64_table[(input[i] >> 2) & 0x3F];
        output[i / 3 * 4 + 1] = b64_table[((input[i] & 0x03) << 4) | ((input[i + 1] & 0xf0) >> 4)];
        output[i / 3 * 4 + 2] = b64_table[((input[i + 1] & 0x0f) << 2) | ((input[i + 2] & 0xc0) >> 6)];
        output[i / 3 * 4 + 3] = b64_table[input[i + 2] & 0x3F];
    }
    
    if (i < input_len) {
        output[i / 3 * 4 + 0] = b64_table[(input[i] >> 2) & 0x3F];
        if (i == (input_len - 1)) {
            output[i / 3 * 4 + 1] = b64_table[(input[i] & 0x03) << 4];
            output[i / 3 * 4 + 2] = '=';
        } else {
            output[i / 3 * 4 + 1] = b64_table[((input[i] & 0x03) << 4) | ((input[i + 1] & 0xf0) >> 4)];
            output[i / 3 * 4 + 2] = b64_table[(input[i + 1] & 0x0f) << 2];
        }
        output[i / 3 * 4 + 3] = '=';
    }

    *output_len = i / 3 * 4 + (i % 3 ? 4 : 0);
}

int main() {
    // Example usage
    upload_image("example.jpg");
    return 0;
}