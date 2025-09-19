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
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    FILE *in = fopen(input_file, "rb");
    if (!in) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(in, 0, SEEK_END);
    long file_size = ftell(in);
    fseek(in, 0, SEEK_SET);

    char *buffer = malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(in);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, in);
    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    fclose(in);
    free(buffer);

    FILE *out = fopen(output_file, "wb");
    if (!out) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fwrite(&bytes_read, sizeof(bytes_read), 1, out);
    fwrite(&checksum, sizeof(checksum), 1, out);

    fclose(out);
    return EXIT_SUCCESS;
}