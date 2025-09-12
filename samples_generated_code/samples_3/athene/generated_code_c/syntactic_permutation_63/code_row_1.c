#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
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
    if (!in) {
        perror("fopen");
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

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *out = fopen(output_file, "w");
    if (!out) {
        perror("fopen");
        free(buffer);
        return 1;
    }

    fprintf(out, "%zu %u\n", bytes_read, checksum);

    fclose(out);
    free(buffer);

    return 0;
}