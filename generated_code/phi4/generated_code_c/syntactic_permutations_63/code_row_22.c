#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *data, size_t length) {
    unsigned long checksum = 0;
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

    FILE *input_file = fopen(argv[1], "rb");
    if (!input_file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    size_t length = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(length);
    if (!buffer) {
        perror("Error allocating memory");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, length, input_file);
    fclose(input_file);

    unsigned long checksum = calculate_checksum(buffer, length);

    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Number of bytes read: %zu\n", length);
    fprintf(output_file, "Checksum: %lu\n", checksum);

    fclose(output_file);
    free(buffer);

    if (checksum == 0) {
        printf("The file is empty.\n");
    } else {
        printf("The file is not empty. Checksum calculated successfully.\n");
    }

    return EXIT_SUCCESS;
}