#include <stdio.h>
#include <stdlib.h>

unsigned char calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned char checksum = 0;
    for (size_t i = 0; i < length; i++) {
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
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(filesize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, filesize, file);
    fclose(file);

    unsigned char checksum = calculate_checksum(buffer, bytes_read);

    free(buffer);

    printf("Number of bytes read: %zu\n", bytes_read);
    printf("Checksum: %u\n", checksum);

    return EXIT_SUCCESS;
}