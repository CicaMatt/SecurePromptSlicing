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
    FILE *file_in, *file_out;
    const char *input_filename = "input.txt";
    const char *output_filename = "output.txt";

    file_in = fopen(input_filename, "rb");
    if (!file_in) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(file_in, 0, SEEK_END);
    size_t file_size = ftell(file_in);
    rewind(file_in);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file_in);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file_in);
    if (bytes_read != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file_in);
        return EXIT_FAILURE;
    }
    
    unsigned long checksum = calculate_checksum(buffer, bytes_read);

    file_out = fopen(output_filename, "w");
    if (!file_out) {
        perror("Error opening output file");
        free(buffer);
        fclose(file_in);
        return EXIT_FAILURE;
    }

    fprintf(file_out, "Bytes read: %zu\nChecksum: %lu\n", bytes_read, checksum);

    free(buffer);
    fclose(file_in);
    fclose(file_out);

    return 0;
}