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
    FILE *input_file = fopen("input.txt", "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    size_t file_size = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, sizeof(unsigned char), file_size, input_file);
    buffer[bytes_read] = '\0'; // Null-terminate the buffer

    unsigned long checksum = calculate_checksum(buffer, bytes_read);

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "%zu\n%lu", bytes_read, checksum);

    free(buffer);
    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}