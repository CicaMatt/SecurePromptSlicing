#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

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
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file_in);
    fclose(file_in);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *file_out = fopen("output.txt", "w");
    if (!file_out) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(file_out, "Bytes read: %zu\n", bytes_read);
    fprintf(file_out, "Checksum: %u\n", checksum);

    fclose(file_out);

    printf("Number of bytes read: %zu\n", bytes_read);
    printf("Checksum: %u\n", checksum);

    return EXIT_SUCCESS;
}