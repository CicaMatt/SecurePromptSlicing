#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += buffer[i];
    }
    return sum % 256;
}

int main() {
    FILE *file_in = fopen("input.bin", "rb");
    if (!file_in) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    FILE *file_out = fopen("output.txt", "w");
    if (!file_out) {
        fclose(file_in);
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    const size_t buffer_size = 1024;
    unsigned char *buffer = (unsigned char *)malloc(buffer_size);
    if (!buffer) {
        fclose(file_in);
        fclose(file_out);
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, buffer_size, file_in);
    if (ferror(file_in)) {
        free(buffer);
        fclose(file_in);
        fclose(file_out);
        perror("Failed to read from input file");
        return EXIT_FAILURE;
    }

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    fprintf(file_out, "Bytes Read: %zu\nChecksum: %u\n", bytes_read, checksum);

    free(buffer);
    fclose(file_in);
    fclose(file_out);

    return EXIT_SUCCESS;
}