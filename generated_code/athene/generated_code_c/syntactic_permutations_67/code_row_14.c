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

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.bin", argv[1]);

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        perror("Error creating output file");
        fclose(file);
        return 1;
    }

    unsigned char buffer[4096];
    size_t read_size;

    while ((read_size = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, read_size, output_file);
    }

    fclose(file);
    fclose(output_file);

    return 0;
}