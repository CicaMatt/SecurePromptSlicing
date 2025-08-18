#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    const char *input_filename = "input.txt";
    const char *output_filename = "output.txt";
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    long file_length = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_length);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_length, input_file);
    if (bytes_read != file_length) {
        perror("Failed to read file");
        free(buffer);
        fclose(input_file);
        return EXIT_FAILURE;
    }

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Bytes read: %zu\nChecksum: %u\n", bytes_read, checksum);

    fclose(output_file);
    fclose(input_file);
    free(buffer);

    return EXIT_SUCCESS;
}