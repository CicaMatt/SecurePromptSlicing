#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += buffer[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *output = fopen("result.txt", "w");
    if (!output) {
        free(buffer);
        fclose(file);
        perror("Error opening output file");
        return 1;
    }

    fprintf(output, "Bytes read: %zu\nChecksum: %u\n", bytes_read, checksum);

    free(buffer);
    fclose(file);
    fclose(output);

    return 0;
}