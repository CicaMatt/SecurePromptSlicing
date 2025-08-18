#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

unsigned long calculate_checksum(const char *buffer, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *input_file = fopen("input.txt", "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        fclose(input_file);
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, input_file);

    unsigned long checksum = calculate_checksum(buffer, bytes_read);
    int is_buffer_empty = (checksum == 0);

    fprintf(output_file, "Bytes read: %zu\n", bytes_read);
    fprintf(output_file, "Checksum: %lu\n", checksum);
    if (is_buffer_empty) {
        fprintf(output_file, "The buffer is empty.\n");
    }

    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}