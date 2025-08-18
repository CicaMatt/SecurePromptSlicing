#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *input_file, *output_file;
    const char *input_filename = "input.txt";
    const char *output_filename = "output.txt";

    input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    size_t buffer_size = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fclose(input_file);
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    fread(buffer, 1, buffer_size, input_file);
    fclose(input_file);

    unsigned int checksum = calculate_checksum(buffer, buffer_size);
    size_t num_bytes = (checksum != 0) ? buffer_size : 0;

    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Number of bytes: %zu\n", num_bytes);
    fprintf(output_file, "Checksum: 0x%08X\n", checksum);

    fclose(output_file);
    free(buffer);

    return EXIT_SUCCESS;
}