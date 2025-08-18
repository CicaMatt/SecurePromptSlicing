#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

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
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read = 0, total_bytes_read = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, input_file)) > 0) {
        total_bytes_read += bytes_read;
    }

    if (ferror(input_file)) {
        perror("Error reading input file");
        fclose(input_file);
        return EXIT_FAILURE;
    }
    
    unsigned long checksum = calculate_checksum(buffer, total_bytes_read);

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Error opening output file");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Bytes Read: %zu\nChecksum: %lu\n", total_bytes_read, checksum);

    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}