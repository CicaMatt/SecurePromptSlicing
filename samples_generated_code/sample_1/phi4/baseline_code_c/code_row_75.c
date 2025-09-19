#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *data, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main() {
    const char *input_filename = "input.txt";
    const char *output_filename = "output.txt";

    FILE *file_in = fopen(input_filename, "rb");
    if (!file_in) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(file_in, 0, SEEK_END);
    size_t file_size = ftell(file_in);
    rewind(file_in);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file_in);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file_in);
    fclose(file_in);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *file_out = fopen(output_filename, "w");
    if (!file_out) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(file_out, "Bytes Read: %zu\n", bytes_read);
    fprintf(file_out, "Checksum: %u\n", checksum);

    fclose(file_out);
    free(buffer);

    return EXIT_SUCCESS;
}