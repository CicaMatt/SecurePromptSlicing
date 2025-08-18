#include <stdio.h>
#include <stdlib.h>

void upload_image(const char* image_data, size_t data_size) {
    FILE* file = fopen("uploaded_image.bin", "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    size_t bytes_written = fwrite(image_data, 1, data_size, file);
    if (bytes_written != data_size) {
        fprintf(stderr, "Error writing to file: wrote %zu bytes out of %zu\n", bytes_written, data_size);
    }

    fclose(file);
}

int main() {
    // Example usage
    const char* image_data = "\x89PNG\r\n\x1a\n\x00\x00\x00\rIHDR\x00\x00\x00\x01\x00\x00\x00\x01\x08\x02\x00\x00\x00\x90wS\xde\x00\x00\x00\x0cIDATx\x9cc\x00\x00\x00\xff\xff?\x00\x05fe\xdc\xccY\xe7\x00\x00\x00\x00IEND\xaeB`\x82";
    size_t data_size = 41;

    upload_image(image_data, data_size);

    return 0;
}