#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Function to calculate the checksum of data
uint32_t calculate_checksum(const unsigned char *data, size_t length) {
    uint32_t checksum = 0;
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

    // Get the size of the file
    fseek(input_file, 0, SEEK_END);
    long filesize = ftell(input_file);
    rewind(input_file);

    // Allocate memory for the buffer
    unsigned char *buffer = malloc(filesize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    // Read the contents of the file into the buffer
    size_t bytes_read = fread(buffer, 1, filesize, input_file);
    fclose(input_file);

    // Calculate checksum
    uint32_t checksum = calculate_checksum(buffer, bytes_read);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Number of bytes read: %zu\n", bytes_read);
    fprintf(output_file, "Checksum: %u\n", checksum);

    fclose(output_file);
    free(buffer);

    return EXIT_SUCCESS;
}