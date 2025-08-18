#include <stdio.h>
#include <stdlib.h>

char* img(char* file) {
    FILE *fp;
    char *buffer;
    long size;

    fp = fopen(file, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = malloc(size + 1);
    if (buffer == NULL) {
        fclose(fp);
        return NULL;
    }

    fread(buffer, 1, size, fp);
    fclose(fp);

    buffer[size] = '\0';
    return buffer;
}

int main() {
    char *file = "example.jpg"; // Example file
    char *image_data = img(file);
    if (image_data) {
        printf("Image data: %s\n", image_data);
        free(image_data);
    } else {
        printf("Failed to read image.\n");
    }
    return 0;
}