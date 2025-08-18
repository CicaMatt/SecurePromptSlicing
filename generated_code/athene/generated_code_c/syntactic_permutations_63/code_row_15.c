#include <stdio.h>
#include <stdlib.h>

int calculate_checksum(const unsigned char *buffer, size_t length) {
    int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    FILE *in = fopen(input_file, "rb");
    if (in == NULL) {
        perror("Error opening input file");
        return 1;
    }

    fseek(in, 0, SEEK_END);
    long file_size = ftell(in);
    fseek(in, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(in);
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, in);
    fclose(in);

    int checksum = calculate_checksum(buffer, bytes_read);

    FILE *out = fopen(output_file, "w");
    if (out == NULL) {
        perror("Error opening output file");
        free(buffer);
        return 1;
    }

    fprintf(out, "%zu %d\n", bytes_read, checksum);

    fclose(out);
    free(buffer);

    return 0;
}