#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += buffer[i];
    }
    return sum;
}

int main() {
    const char *input_filename = "input.bin";
    const char *output_filename = "output.txt";
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    // Determine the size of the file
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    rewind(input_file);

    // Allocate memory for the buffer
    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    // Read the file into the buffer
    size_t bytes_read = fread(buffer, 1, file_size, input_file);
    fclose(input_file);

    // Calculate the checksum
    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    // Write the number of bytes read and the checksum to another file
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        exit(EXIT_FAILURE);
    }
    fprintf(output_file, "Bytes Read: %zu\nChecksum: %u\n", bytes_read, checksum);
    fclose(output_file);

    // Free the allocated memory
    free(buffer);

    return 0;
}