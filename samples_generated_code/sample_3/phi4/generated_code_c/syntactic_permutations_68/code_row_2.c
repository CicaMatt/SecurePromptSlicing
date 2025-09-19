#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include necessary libraries for file operations and base64 encoding
#include "base64.h"

void upload_image(const char *image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open the image file.\n");
        return;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory for file content
    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return;
    }

    // Read the file into buffer
    fread(buffer, 1, file_size, file);
    fclose(file);

    // Convert to base64
    char *encoded = base64_encode(buffer, file_size);
    free(buffer);

    if (!encoded) {
        fprintf(stderr, "Base64 encoding failed.\n");
        return;
    }

    // Output the image name and base64 string
    const char *file_name = strrchr(image_path, '/');
    if (!file_name) {
        file_name = image_path;
    } else {
        ++file_name;  // Move past the '/'
    }
    printf("Image Name: %s\n", file_name);
    printf("Base64 String:\n%s\n", encoded);

    free(encoded);  // Clean up
}

int main() {
    const char *image_path = "path/to/your/image.jpg";  // Replace with actual image path
    upload_image(image_path);
    return 0;
}
