#include <stdio.h>
#include <stdlib.h>

unsigned char calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned char checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    const char *input_filename = "input.bin";
    const char *output_filename = "output.bin";
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    long file_length = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_length);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_length, input_file);
    fclose(input_file);

    if (bytes_read != file_length) {
        fprintf(stderr, "Failed to read entire file\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    unsigned char checksum = calculate_checksum(buffer, file_length);
    if (checksum == 0) {
        FILE *output_file = fopen(output_filename, "wb");
        if (!output_file) {
            perror("Failed to open output file");
            free(buffer);
            return EXIT_FAILURE;
        }
        fwrite(buffer, 1, file_length, output_file);
        fputc(checksum, output_file);
        fclose(output_file);
    }

    free(buffer);
    return EXIT_SUCCESS;
}