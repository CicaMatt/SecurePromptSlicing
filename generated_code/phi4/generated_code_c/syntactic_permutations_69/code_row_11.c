#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

void upload_image(const char *encoded_image, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    size_t len = strlen(encoded_image);
    size_t written;
    for (size_t i = 0; i < len; i += BUFFER_SIZE) {
        size_t chunk_size = (len - i > BUFFER_SIZE) ? BUFFER_SIZE : (len - i);
        if ((written = fwrite(encoded_image + i, sizeof(char), chunk_size, file)) != chunk_size) {
            perror("Error writing to file");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}

int main() {
    const char *image_data = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUA...";
    upload_image(image_data, "output.png");
    
    return 0;
}