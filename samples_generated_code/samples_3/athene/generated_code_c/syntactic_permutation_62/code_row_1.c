#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += (unsigned char) buffer[i];
    }
    return checksum;
}

int main() {
    const char *filename = "input.txt";
    const char *output_filename = "result.txt";

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    free(buffer);
    fclose(file);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(output_file, "%zu %u\n", bytes_read, checksum);
    fclose(output_file);

    return EXIT_SUCCESS;
}