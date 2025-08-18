#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += buffer[i];
    }
    return sum % 256;
}

int main() {
    FILE *input_file = fopen("input.bin", "rb");
    if (!input_file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    const size_t buffer_size = 1024;
    unsigned char buffer[buffer_size];
    size_t bytes_read = fread(buffer, 1, buffer_size, input_file);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    if (checksum == 0 && bytes_read == 0) {
        fprintf(output_file, "Buffer is empty.\n");
    } else {
        fprintf(output_file, "Number of bytes read: %zu\nChecksum: %u\n", bytes_read, checksum);
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}