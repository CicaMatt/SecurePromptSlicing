#include <stdio.h>
#include <stdlib.h>

unsigned char calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned char sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += buffer[i];
    }
    return sum;
}

int main() {
    FILE *file = fopen("input.txt", "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_length);
    if (!buffer) {
        fclose(file);
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, 1, file_length, file);
    fclose(file);

    unsigned char checksum = calculate_checksum(buffer, bytes_read);

    printf("Number of bytes read: %zu\n", bytes_read);
    printf("Checksum: %u\n", checksum);

    free(buffer);
    return 0;
}