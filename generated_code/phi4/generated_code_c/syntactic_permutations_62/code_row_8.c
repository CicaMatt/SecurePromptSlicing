#include <stdio.h>
#include <stdlib.h>

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

    fseek(input_file, 0, SEEK_END);
    size_t length = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = (unsigned char *)malloc(length);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, length, input_file);
    fclose(input_file);

    unsigned int checksum = calculate_checksum(buffer, length);

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Number of bytes read: %zu\n", length);
    fprintf(output_file, "Checksum: %u\n", checksum);

    fclose(output_file);
    free(buffer);

    return 0;
}