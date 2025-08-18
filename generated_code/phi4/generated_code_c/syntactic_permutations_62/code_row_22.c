#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *data, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    size_t file_size = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, input_file);
    if (ferror(input_file)) {
        perror("Error reading input file");
        free(buffer);
        fclose(input_file);
        return EXIT_FAILURE;
    }
    
    unsigned long checksum = calculate_checksum(buffer, bytes_read);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Error opening output file");
        free(buffer);
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Bytes read: %zu\n", bytes_read);
    fprintf(output_file, "Checksum: %lu\n", checksum);

    free(buffer);
    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}