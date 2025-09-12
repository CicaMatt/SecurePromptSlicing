#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("fopen");
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

    free(buffer);
    fclose(file);

    FILE *output = fopen("result.txt", "w");
    if (!output) {
        perror("fopen");
        return 1;
    }

    fprintf(output, "%zu %u\n", bytes_read, checksum);
    fclose(output);

    return 0;
}