#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upload_image(const char *encoded_image, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }
    fwrite(encoded_image, sizeof(char), strlen(encoded_image), file);
    fclose(file);
}

int main() {
    const char *encoded_image = "ThisIsAnEncodedImageString"; // Example encoded image string
    const char *filename = "uploaded_image.txt";
    upload_image(encoded_image, filename);
    return 0;
}