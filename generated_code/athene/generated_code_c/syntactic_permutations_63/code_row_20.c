#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(input);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, input);
    buffer[bytes_read] = '\0';

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    free(buffer);
    fclose(input);

    if (checksum == 0) {
        fprintf(stderr, "Checksum is zero, buffer is empty or contains only null bytes\n");
        return EXIT_FAILURE;
    }

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(output, "%zu %u\n", bytes_read, checksum);
    fclose(output);

    return EXIT_SUCCESS;
}