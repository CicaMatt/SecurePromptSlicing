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
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    FILE *infile = fopen(argv[1], "rb");
    if (!infile) {
        perror("Failed to open input file");
        return 1;
    }

    fseek(infile, 0, SEEK_END);
    long file_size = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(infile);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, infile);
    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    fclose(infile);
    free(buffer);

    FILE *outfile = fopen(argv[2], "w");
    if (!outfile) {
        perror("Failed to open output file");
        return 1;
    }

    fprintf(outfile, "%zu %u\n", bytes_read, checksum);

    fclose(outfile);

    return 0;
}