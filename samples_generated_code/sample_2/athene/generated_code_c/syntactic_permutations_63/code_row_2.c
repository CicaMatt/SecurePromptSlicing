#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += (unsigned char)buffer[i];
    }
    return sum;
}

int main() {
    const char *input_filename = "input.txt";
    const char *output_filename = "output.txt";

    FILE *infile = fopen(input_filename, "rb");
    if (!infile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(infile, 0, SEEK_END);
    long file_size = ftell(infile);
    rewind(infile);

    char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(infile);
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, infile);
    fclose(infile);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *outfile = fopen(output_filename, "w");
    if (!outfile) {
        free(buffer);
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(outfile, "%zu %u\n", bytes_read, checksum);
    fclose(outfile);

    free(buffer);
    return EXIT_SUCCESS;
}