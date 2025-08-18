#include <stdio.h>
#include <stdlib.h>

unsigned char calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned char checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    const char *input_file = "input.txt";
    const char *output_file = "result.txt";
    FILE *file_in = fopen(input_file, "rb");
    if (!file_in) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(file_in, 0, SEEK_END);
    long file_size = ftell(file_in);
    fseek(file_in, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file_in);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file_in);
    fclose(file_in);

    unsigned char checksum = calculate_checksum(buffer, bytes_read);

    FILE *file_out = fopen(output_file, "w");
    if (!file_out) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(file_out, "Bytes read: %zu\nChecksum: %u\n", bytes_read, checksum);
    fclose(file_out);

    free(buffer);
    return EXIT_SUCCESS;
}