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
    rewind(file_in);

    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    if (!buffer) {
        perror("Failed to allocate memory for buffer");
        fclose(file_in);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file_in);
    fclose(file_in);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *file_out = fopen("output.txt", "w");
    if (!file_out) {
        perror("Failed to open output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(file_out, "Number of bytes read: %zu\n", bytes_read);
    fprintf(file_out, "Checksum: %u\n", checksum);

    fclose(file_out);
    free(buffer);

    return EXIT_SUCCESS;
}