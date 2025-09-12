#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += buffer[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        perror("Error opening input file");
        return 1;
    }

    fseek(in, 0, SEEK_END);
    long file_size = ftell(in);
    fseek(in, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(in);
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, in);
    fclose(in);

    if (bytes_read == 0) {
        free(buffer);
        FILE *out = fopen(argv[2], "w");
        if (!out) {
            perror("Error opening output file");
            return 1;
        }
        fprintf(out, "0 0\n");
        fclose(out);
        return 0;
    }

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    free(buffer);

    FILE *out = fopen(argv[2], "w");
    if (!out) {
        perror("Error opening output file");
        return 1;
    }
    fprintf(out, "%zu %u\n", bytes_read, checksum);
    fclose(out);

    return 0;
}