#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to encode binary data to base64
void base64_encode(const unsigned char *data, size_t input_length, char *encoded_data) {
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int output_length = 4 * ((input_length + 2) / 3);
    encoded_data[output_length] = '\0';

    for (int i = 0, j = 0; i < input_length;) {
        unsigned int octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        unsigned int octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        unsigned int octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        unsigned int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < (output_length - input_length - 1) / 3 + 1; i++) {
        encoded_data[output_length - 1 - i] = '=';
    }
}

// Function to simulate uploading an image
void upload_image(const char *image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *image_data = (unsigned char *)malloc(file_size + 1);
    if (!image_data) {
        perror("Failed to allocate memory");
        fclose(file);
        return;
    }

    size_t bytes_read = fread(image_data, 1, file_size, file);
    fclose(file);

    if (bytes_read != file_size) {
        fprintf(stderr, "Error reading file\n");
        free(image_data);
        return;
    }

    char *base64_string = (char *)malloc((file_size * 4 / 3) + 1);
    if (!base64_string) {
        perror("Failed to allocate memory for base64 string");
        free(image_data);
        return;
    }

    base64_encode(image_data, file_size, base64_string);

    printf("Image name: %s\n", image_path);
    printf("Base64 encoded data: %s\n", base64_string);

    // Insert the image name and base64 string into a database or another system here

    free(base64_string);
    free(image_data);
}

int main() {
    upload_image("path/to/image.jpg");
    return 0;
}