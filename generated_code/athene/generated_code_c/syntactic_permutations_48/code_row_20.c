#include <stdio.h>
#include <stdlib.h>

char* img(char* file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    char *buffer = malloc(fsize + 1);
    fread(buffer, fsize, 1, fp);
    fclose(fp);
    buffer[fsize] = '\0';
    return buffer;
}

int main() {
    // Example usage
    char* file = "example.png";
    char* image_data = img(file);
    
    if (image_data != NULL) {
        printf("Image data read successfully.\n");
        free(image_data);
    } else {
        fprintf(stderr, "Failed to read image file.\n");
    }
    return 0;
}