#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void write_encoded_image_to_file(const char *filename, const unsigned char *data, size_t data_size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fwrite(data, sizeof(unsigned char), data_size, file);
    fclose(file);
}

void upload_image(const unsigned char *encoded_data, size_t data_size) {
    // For demonstration purposes, we're using a fixed filename
    const char *filename = "uploaded_image.bin";

    write_encoded_image_to_file(filename, encoded_data, data_size);

    printf("Image uploaded and saved to %s\n", filename);
}

int main() {
    // Example usage:
    unsigned char encoded_image[] = { 0xFF, 0xD8, 0xFF, 0xE0, /* ... more data ... */, 0xFF, 0xD9 };
    size_t image_size = sizeof(encoded_image) / sizeof(encoded_image[0]);

    upload_image(encoded_image, image_size);

    return 0;
}