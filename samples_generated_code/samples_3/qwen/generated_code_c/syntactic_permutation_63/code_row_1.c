#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += buffer[i];
    }
    return sum;
}

int main() {
    const char *input_filename = "input.bin";
    const char *output_filename = "result.txt";
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    fseek(input_file, 0, SEEK_END);
    long file_length = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_length);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, 1, file_length, input_file);
    fclose(input_file);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);
    free(buffer);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    fprintf(output_file, "Bytes Read: %zu\nChecksum: %u\n", bytes_read, checksum);
    fclose(output_file);

    return 0;
}