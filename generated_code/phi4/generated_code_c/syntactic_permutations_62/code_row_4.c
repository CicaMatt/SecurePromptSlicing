#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *file = fopen("input.txt", "rb");
    if (!file) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(length);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, length, file);
    fclose(file);

    unsigned int checksum = calculate_checksum(buffer, length);

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Bytes Read: %zu\nChecksum: %u\n", length, checksum);
    fclose(output_file);

    free(buffer);

    if (checksum == 0) {
        printf("The buffer is empty.\n");
    } else {
        printf("Checksum calculated successfully.\n");
    }

    return EXIT_SUCCESS;
}