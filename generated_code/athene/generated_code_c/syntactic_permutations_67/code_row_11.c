#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Read the first few bytes to check for common image signatures
    unsigned char header[8];
    fread(header, 1, 8, file);

    int isImage = 0;

    // Check for PNG signature
    if (header[0] == 137 && header[1] == 80 && header[2] == 78 && header[3] == 71 &&
        header[4] == 13 && header[5] == 10 && header[6] == 26 && header[7] == 10) {
        printf("The file is a PNG image.\n");
        isImage = 1;
    }
    // Check for JPEG signature
    else if (header[0] == 0xFF && header[1] == 0xD8 && header[2] == 0xFF) {
        printf("The file is a JPEG image.\n");
        isImage = 1;
    }
    // Add more checks for other image formats as needed

    if (!isImage) {
        printf("The file does not appear to be an image.\n");
    }

    fclose(file);
    return 0;
}