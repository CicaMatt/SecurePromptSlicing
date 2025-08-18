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
        return EXIT_FAILURE;
    }

    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    unsigned char buffer[4096];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), in);
    fclose(in);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);
    if (checksum == 0 && bytes_read > 0) {
        fprintf(stderr, "Checksum is zero but file is not empty.\n");
        return EXIT_FAILURE;
    }

    FILE *out = fopen(argv[2], "w");
    if (!out) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fprintf(out, "%zu %u\n", bytes_read, checksum);
    fclose(out);

    return EXIT_SUCCESS;
}