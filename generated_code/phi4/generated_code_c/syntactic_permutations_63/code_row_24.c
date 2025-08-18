#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *data, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main() {
    FILE *input_file = fopen("input.txt", "rb");
    if (!input_file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    size_t length = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = (unsigned char *)malloc(length);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, length, input_file);
    fclose(input_file);

    unsigned int checksum = calculate_checksum(buffer, length);

    if (checksum == 0) {
        FILE *output_file = fopen("output.txt", "wb");
        if (!output_file) {
            perror("Error opening output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fwrite(&checksum, sizeof(checksum), 1, output_file);
        fwrite(buffer, 1, length, output_file);

        fclose(output_file);
    } else {
        printf("Checksum is not zero. No output file created.\n");
    }

    free(buffer);
    return EXIT_SUCCESS;
}