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
    FILE *file_in = fopen("input.txt", "rb");
    if (!file_in) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(file_in, 0, SEEK_END);
    long file_size = ftell(file_in);
    fseek(file_in, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file_in);
        return EXIT_FAILURE;
    }

    size_t read_bytes = fread(buffer, 1, file_size, file_in);
    if (read_bytes == 0 && ferror(file_in)) {
        perror("Failed to read from input file");
        free(buffer);
        fclose(file_in);
        return EXIT_FAILURE;
    }
    
    unsigned int checksum = calculate_checksum(buffer, read_bytes);

    FILE *file_out = fopen("output.txt", "w");
    if (!file_out) {
        perror("Failed to open output file");
        free(buffer);
        fclose(file_in);
        return EXIT_FAILURE;
    }

    fprintf(file_out, "Bytes Read: %zu\nChecksum: %u\n", read_bytes, checksum);

    free(buffer);
    fclose(file_in);
    fclose(file_out);

    return 0;
}