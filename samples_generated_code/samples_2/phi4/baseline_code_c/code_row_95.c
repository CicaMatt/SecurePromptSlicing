#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *data, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main() {
    const char *input_filename = "input.txt";
    const char *output_filename = "output.txt";

    FILE *file_input = fopen(input_filename, "rb");
    if (file_input == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(file_input, 0, SEEK_END);
    long file_size = ftell(file_input);
    rewind(file_input);

    if (file_size < 0) {
        fclose(file_input);
        fprintf(stderr, "Failed to determine the size of the file\n");
        return EXIT_FAILURE;
    }

    unsigned char *buffer = malloc((size_t)file_size);
    if (buffer == NULL) {
        fclose(file_input);
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file_input);
    fclose(file_input);

    if (bytes_read != file_size) {
        free(buffer);
        fprintf(stderr, "Failed to read the complete file\n");
        return EXIT_FAILURE;
    }

    unsigned long checksum = calculate_checksum(buffer, bytes_read);
    int is_empty = (checksum == 0);

    FILE *file_output = fopen(output_filename, "w");
    if (file_output == NULL) {
        free(buffer);
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(file_output, "Bytes Read: %zu\n", bytes_read);
    fprintf(file_output, "Checksum: %lu\n", checksum);
    fprintf(file_output, "Buffer is empty: %s\n", is_empty ? "Yes" : "No");

    fclose(file_output);
    free(buffer);

    return EXIT_SUCCESS;
}