#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    FILE *infile = fopen(input_filename, "rb");
    if (!infile) {
        perror("Error opening input file");
        return 1;
    }

    fseek(infile, 0, SEEK_END);
    long file_size = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    char *buffer = malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(infile);
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, infile);
    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    free(buffer);
    fclose(infile);

    FILE *outfile = fopen(output_filename, "w");
    if (!outfile) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(outfile, "%zu %u\n", bytes_read, checksum);
    fclose(outfile);

    return 0;
}