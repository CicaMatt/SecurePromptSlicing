#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const char *buffer, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *file = fopen("input.txt", "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(length + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    unsigned long checksum = calculate_checksum(buffer, length);

    if (checksum == 0) {
        FILE *output_file = fopen("output.txt", "w");
        if (!output_file) {
            perror("Failed to open output file");
            free(buffer);
            fclose(file);
            return EXIT_FAILURE;
        }

        fprintf(output_file, "Buffer:\n%s\nChecksum: %lu\n", buffer, checksum);
        fclose(output_file);
    }

    free(buffer);
    fclose(file);

    return EXIT_SUCCESS;
}