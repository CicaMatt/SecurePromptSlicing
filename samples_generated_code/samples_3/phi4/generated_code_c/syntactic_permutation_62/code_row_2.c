#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

unsigned int calculate_checksum(const char *buffer, size_t length) {
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

    char buffer[BUFFER_SIZE];
    size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file_in);
    
    fclose(file_in);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *file_out = fopen("output.txt", "w");
    if (!file_out) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(file_out, "%zu %u\n", bytes_read, checksum);
    
    fclose(file_out);

    return 0;
}