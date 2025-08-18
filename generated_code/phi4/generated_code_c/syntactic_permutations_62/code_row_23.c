#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *file = fopen("input.txt", "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(length);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, length, file);
    fclose(file);

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
    }

    free(buffer);
    return EXIT_SUCCESS;
}