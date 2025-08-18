#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum & 0xFFFFFFFF;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(input, 0, SEEK_END);
    long length = ftell(input);
    fseek(input, 0, SEEK_SET);

    char *buffer = malloc(length);
    if (fread(buffer, 1, length, input) != length) {
        perror("Failed to read file");
        fclose(input);
        free(buffer);
        return EXIT_FAILURE;
    }

    fclose(input);

    unsigned int checksum = calculate_checksum(buffer, length);

    if (checksum == 0) {
        FILE *output = fopen(argv[2], "wb");
        if (!output) {
            perror("Failed to open output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fwrite(buffer, 1, length, output);
        fwrite(&checksum, sizeof(checksum), 1, output);

        fclose(output);
    }

    free(buffer);
    return EXIT_SUCCESS;
}