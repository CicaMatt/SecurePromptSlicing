#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *data, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main() {
    const char *input_filename = "input.txt";
    const char *output_filename = "output.txt";

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    size_t file_size = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, file_size, input_file);
    fclose(input_file);

    unsigned long checksum = calculate_checksum(buffer, file_size);
    int is_empty = (checksum == 0);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Bytes Read: %zu\n", file_size);
    fprintf(output_file, "Checksum: %lu\n", checksum);
    fprintf(output_file, "Buffer is Empty: %s\n", is_empty ? "Yes" : "No");

    fclose(output_file);
    free(buffer);

    return EXIT_SUCCESS;
}