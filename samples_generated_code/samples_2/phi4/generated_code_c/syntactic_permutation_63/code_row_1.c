#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input_file = fopen(argv[1], "rb");
    if (!input_file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    size_t file_size = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, input_file);
    fclose(input_file);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);
    free(buffer);

    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Bytes read: %zu\n", bytes_read);
    fprintf(output_file, "Checksum: %u\n", checksum);

    fclose(output_file);

    return EXIT_SUCCESS;
}