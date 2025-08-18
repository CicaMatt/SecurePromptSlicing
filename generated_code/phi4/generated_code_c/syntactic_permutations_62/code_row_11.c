#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(unsigned char *buffer, size_t length) {
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
    size_t file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fread(buffer, sizeof(unsigned char), file_size, input_file);
    fclose(input_file);

    unsigned long checksum = calculate_checksum(buffer, file_size);
    
    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Number of bytes read: %zu\nChecksum: %lu\n", file_size, checksum);
    fclose(output_file);

    free(buffer);
    return 0;
}