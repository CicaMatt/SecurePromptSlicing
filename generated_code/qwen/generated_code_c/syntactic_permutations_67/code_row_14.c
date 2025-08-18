#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_image_file output_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        perror("Failed to open output file");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    unsigned char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
        if (fwrite(buffer, 1, bytes_read, output_file) != bytes_read) {
            perror("Failed to write to output file");
            fclose(input_file);
            fclose(output_file);
            return EXIT_FAILURE;
        }
    }

    if (ferror(input_file)) {
        perror("Error reading from input file");
        fclose(input_file);
        fclose(output_file);
        return EXIT_FAILURE;
    }

    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}