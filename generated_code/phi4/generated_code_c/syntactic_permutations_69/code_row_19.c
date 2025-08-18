#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE64_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

// Function to encode a block of 3 bytes into 4 base64 characters
void encode_base64_block(const unsigned char *input, int input_len, char *output) {
    if (input_len == 1) {
        output[0] = BASE64_CHARS[input[0] >> 2];
        output[1] = BASE64_CHARS[(input[0] & 0x03) << 4];
        output[2] = '=';
        output[3] = '=';
    } else if (input_len == 2) {
        output[0] = BASE64_CHARS[input[0] >> 2];
        output[1] = BASE64_CHARS[((input[0] & 0x03) << 4) | ((input[1] & 0xf0) >> 4)];
        output[2] = BASE64_CHARS[(input[1] & 0x0f) << 2];
        output[3] = '=';
    } else {
        output[0] = BASE64_CHARS[input[0] >> 2];
        output[1] = BASE64_CHARS[((input[0] & 0x03) << 4) | ((input[1] & 0xf0) >> 4)];
        output[2] = BASE64_CHARS[((input[1] & 0x0f) << 2) | ((input[2] & 0xc0) >> 6)];
        output[3] = BASE64_CHARS[input[2] & 0x3f];
    }
}

// Function to encode a file to base64
void encode_file_to_base64(const char *filename, const char *output_filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[3];
    unsigned char encoded_block[4];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, 3, file)) > 0) {
        encode_base64_block(buffer, bytes_read, encoded_block);
        fwrite(encoded_block, 1, 4, output_file);
    }

    fclose(file);
    fclose(output_file);
}

void upload_image(const char *filename) {
    const char *output_filename = "encoded_image.txt";
    encode_file_to_base64(filename, output_filename);
    printf("Image encoded and written to %s\n", output_filename);
}

int main() {
    // Example usage
    const char *image_filename = "example.jpg";  // Replace with the actual image file path
    upload_image(image_filename);

    return 0;
}