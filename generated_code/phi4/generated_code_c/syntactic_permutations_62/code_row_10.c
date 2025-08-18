#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *data, size_t length) {
    unsigned long sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += data[i];
    }
    return sum;
}

int main() {
    FILE *file_in, *file_out;
    const char *input_filename = "input.bin";
    const char *output_filename = "checksum.txt";
    
    file_in = fopen(input_filename, "rb");
    if (!file_in) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(file_in, 0, SEEK_END);
    long file_size = ftell(file_in);
    rewind(file_in);

    unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char) * file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file_in);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, sizeof(unsigned char), file_size, file_in);
    if (bytes_read != file_size && !feof(file_in)) {
        free(buffer);
        fclose(file_in);
        perror("Error reading input file");
        return EXIT_FAILURE;
    }
    
    unsigned long checksum = calculate_checksum(buffer, bytes_read);

    file_out = fopen(output_filename, "w");
    if (!file_out) {
        free(buffer);
        fclose(file_in);
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(file_out, "Number of Bytes Read: %zu\n", bytes_read);
    fprintf(file_out, "Checksum: %lu\n", checksum);

    free(buffer);
    fclose(file_in);
    fclose(file_out);

    return EXIT_SUCCESS;
}