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

    char *output_filename = "stored_image";
    FILE *output = fopen(output_filename, "wb");
    if (!output) {
        fclose(file);
        perror("Error creating output file");
        return 1;
    }

    const size_t bufferSize = 4096;
    unsigned char buffer[bufferSize];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, bufferSize, file)) > 0) {
        fwrite(buffer, 1, bytesRead, output);
    }

    fclose(file);
    fclose(output);

    printf("Image stored successfully as %s\n", output_filename);
    return 0;
}