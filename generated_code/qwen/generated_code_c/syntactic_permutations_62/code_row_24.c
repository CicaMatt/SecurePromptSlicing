#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += buffer[i];
    }
    return sum % 256;
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
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, input_file);
    if (bytes_read != file_size) {
        perror("Failed to read file");
        free(buffer);
        fclose(input_file);
        return EXIT_FAILURE;
    }
    fclose(input_file);

    unsigned int checksum = calculate_checksum(buffer, file_size);
    if (checksum == 0) {
        FILE *output_file = fopen(output_filename, "wb");
        if (!output_file) {
            perror("Failed to open output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fwrite(buffer, 1, file_size, output_file);
        fclose(output_file);
    }

    free(buffer);
    return EXIT_SUCCESS;
}