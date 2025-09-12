#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
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
    long filesize = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = (unsigned char *)malloc(filesize + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, sizeof(unsigned char), filesize, input_file);
    buffer[bytes_read] = '\0';

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Bytes read: %zu\nChecksum: %u\n", bytes_read, checksum);

    fclose(input_file);
    fclose(output_file);
    free(buffer);

    return 0;
}