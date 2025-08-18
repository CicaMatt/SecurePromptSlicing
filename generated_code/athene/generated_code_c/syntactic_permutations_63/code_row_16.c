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

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("Failed to open input file");
        return 1;
    }

    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(input);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, input);
    fclose(input);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);
    free(buffer);

    FILE *output = fopen(argv[2], "wb");
    if (!output) {
        perror("Failed to open output file");
        return 1;
    }

    fwrite(&bytes_read, sizeof(size_t), 1, output);
    fwrite(&checksum, sizeof(unsigned int), 1, output);
    fclose(output);

    if (checksum == 0 && bytes_read > 0) {
        fprintf(stderr, "Warning: Checksum is 0 but buffer is not empty\n");
    }

    return 0;
}