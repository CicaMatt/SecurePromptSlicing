#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
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
    size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, input_file);
    if (ferror(input_file)) {
        perror("Error reading input file");
        fclose(input_file);
        return EXIT_FAILURE;
    }
    
    fclose(input_file);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Number of bytes: %zu\nChecksum: %u\n", bytes_read, checksum);
    
    fclose(output_file);

    return EXIT_SUCCESS;
}