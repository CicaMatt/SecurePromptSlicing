#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void upload_image(const char *base64_data, const char *output_filename);

int main() {
    const char *image_base64 = "iVBORw0KGgoAAAANSUhEUgAAAAUA...";
    const char *filename = "output.png";
    
    upload_image(image_base64, filename);
    
    return 0;
}

void upload_image(const char *base64_data, const char *output_filename) {
    FILE *file = fopen(output_filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    // Simulate base64 decoding and write directly to file
    // In practice, use a proper library or function for base64 decoding
    const char *decoded_data = "\x89PNG\r\n\x1a\n..."; // Placeholder for actual decoded data

    if (fwrite(decoded_data, 1, strlen(decoded_data), file) != strlen(decoded_data)) {
        perror("Failed to write image data");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}