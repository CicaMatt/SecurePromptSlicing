#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *data, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    size_t file_size = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, file_size, input_file);
    fclose(input_file);

    unsigned int checksum = calculate_checksum(buffer, file_size);

    if (checksum == 0) {
        FILE *output_file = fopen(output_filename, "wb");
        if (!output_file) {
            perror("Error opening output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fwrite(&file_size, sizeof(file_size), 1, output_file);
        fwrite(buffer, 1, file_size, output_file);

        fclose(output_file);
    }

    free(buffer);
    return 0;
}