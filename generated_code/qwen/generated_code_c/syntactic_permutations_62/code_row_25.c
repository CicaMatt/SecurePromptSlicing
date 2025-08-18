#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input_file = fopen(argv[1], "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        fclose(input_file);
        perror("Failed to allocate memory for buffer");
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, input_file);
    fclose(input_file);

    if (bytes_read != file_size) {
        free(buffer);
        fprintf(stderr, "Failed to read the entire file\n");
        return EXIT_FAILURE;
    }

    unsigned int checksum = calculate_checksum(buffer, file_size);

    FILE *output_file = fopen(argv[2], "wb");
    if (!output_file) {
        free(buffer);
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    if (checksum == 0) {
        fwrite(buffer, 1, file_size, output_file);
        fprintf(output_file, "\nChecksum: %u\n", checksum);
    }

    fclose(output_file);
    free(buffer);

    return EXIT_SUCCESS;
}