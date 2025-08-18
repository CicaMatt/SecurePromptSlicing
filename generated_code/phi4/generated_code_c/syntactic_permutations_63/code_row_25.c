#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *file_in = fopen("input.txt", "rb");
    if (!file_in) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    FILE *file_out = fopen("output.txt", "wb");
    if (!file_out) {
        perror("Failed to open output file");
        fclose(file_in);
        return EXIT_FAILURE;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t total_bytes_read = 0;

    while (size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file_in)) {
        total_bytes_read += bytes_read;
    }

    if (ferror(file_in)) {
        perror("Error reading input file");
        fclose(file_in);
        fclose(file_out);
        return EXIT_FAILURE;
    }
    
    unsigned int checksum = calculate_checksum(buffer, total_bytes_read);

    if (checksum == 0) {
        fwrite(&total_bytes_read, sizeof(total_bytes_read), 1, file_out);
        fwrite(buffer, 1, total_bytes_read, file_out);
    }

    fclose(file_in);
    fclose(file_out);

    return EXIT_SUCCESS;
}