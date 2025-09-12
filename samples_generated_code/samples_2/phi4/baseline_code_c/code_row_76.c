#include <stdio.h>
#include <stdlib.h>

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

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    rewind(input_file);

    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, input_file);
    buffer[file_size] = '\0'; // Null-terminate the buffer

    fclose(input_file);

    unsigned long checksum = calculate_checksum(buffer, bytes_read);

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Bytes read: %zu\nChecksum: %lu\n", bytes_read, checksum);

    fclose(output_file);
    free(buffer);

    return EXIT_SUCCESS;
}