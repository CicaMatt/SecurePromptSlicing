#include <stdio.h>
#include <stdlib.h>

unsigned char calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned char checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *file = fopen("input.txt", "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(filesize);
    if (!buffer) {
        fclose(file);
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, 1, filesize, file);
    fclose(file);

    unsigned char checksum = calculate_checksum(buffer, bytes_read);

    FILE *output_file = fopen("result.txt", "w");
    if (!output_file) {
        free(buffer);
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    fprintf(output_file, "Bytes read: %zu\nChecksum: %u\n", bytes_read, checksum);
    fclose(output_file);

    free(buffer);

    return 0;
}