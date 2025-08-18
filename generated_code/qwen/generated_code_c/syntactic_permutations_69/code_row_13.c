#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGE_BUFFER_SIZE 1024

void encode_image(unsigned char* buffer, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        buffer[i] ^= 0xFF; // Simple encoding by XOR with 0xFF
    }
}

void upload_image(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    unsigned char image_buffer[IMAGE_BUFFER_SIZE];
    size_t bytes_read;

    FILE* output_file = fopen("encoded_image.bin", "wb");
    if (!output_file) {
        perror("Failed to create output file");
        fclose(file);
        return;
    }

    while ((bytes_read = fread(image_buffer, 1, IMAGE_BUFFER_SIZE, file)) > 0) {
        encode_image(image_buffer, bytes_read);
        fwrite(image_buffer, 1, bytes_read, output_file);
    }

    fclose(file);
    fclose(output_file);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    upload_image(argv[1]);
    return EXIT_SUCCESS;
}