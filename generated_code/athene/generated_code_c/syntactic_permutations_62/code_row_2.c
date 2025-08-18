#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t calculate_checksum(const char *buffer, size_t length) {
    uint32_t checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("fopen");
        return 1;
    }

    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(input);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, input);
    uint32_t checksum = calculate_checksum(buffer, bytes_read);

    free(buffer);
    fclose(input);

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        perror("fopen");
        return 1;
    }

    fprintf(output, "%zu %u\n", bytes_read, checksum);

    fclose(output);
    return 0;
}