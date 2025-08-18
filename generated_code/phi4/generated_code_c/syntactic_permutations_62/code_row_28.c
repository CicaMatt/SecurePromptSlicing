#include <stdio.h>
#include <stdlib.h>

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
    size_t total_bytes_read = 0;

    while (size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, input_file)) {
        total_bytes_read += bytes_read;
    }

    fclose(input_file);

    if (total_bytes_read == 0) {
        printf("Buffer is empty.\n");
    } else {
        unsigned long checksum = calculate_checksum(buffer, total_bytes_read);
        
        FILE *output_file = fopen("output.txt", "w");
        if (!output_file) {
            perror("Error opening output file");
            return EXIT_FAILURE;
        }
        
        fprintf(output_file, "Number of bytes read: %zu\n", total_bytes_read);
        fprintf(output_file, "Checksum: %lu\n", checksum);

        fclose(output_file);
    }

    return 0;
}