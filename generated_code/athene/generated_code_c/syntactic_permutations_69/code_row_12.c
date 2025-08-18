#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeToFile(const char *filename, const unsigned char *data, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fwrite(data, 1, length, file);
    fclose(file);
}

void upload_image(const unsigned char *image_data, size_t image_size, const char *filename) {
    writeToFile(filename, image_data, image_size);
}