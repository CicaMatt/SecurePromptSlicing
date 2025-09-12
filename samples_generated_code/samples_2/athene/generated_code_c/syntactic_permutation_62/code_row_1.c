#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}

int main() {
    const char *input_filename = "input.txt";
    const char *output_filename = "output.txt";

    FILE *file = fopen(input_filename, "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(file);
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    fclose(file);
    free(buffer);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(output_file, "%zu %u\n", bytes_read, checksum);
    fclose(output_file);

    return EXIT_SUCCESS;
}