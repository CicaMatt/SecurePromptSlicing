#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upload_image(const char* image_data, size_t data_size, const char* filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    
    size_t written = fwrite(image_data, 1, data_size, file);
    if (written != data_size) {
        fprintf(stderr, "Error writing to file: only %zu bytes of %zu bytes written\n", written, data_size);
    }
    
    fclose(file);
}

int main() {
    // Example usage
    const char* image_data = "This is a placeholder for encoded image data";
    size_t data_size = strlen(image_data);
    const char* filename = "uploaded_image.bin";

    upload_image(image_data, data_size, filename);

    return 0;
}