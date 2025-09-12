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
    FILE *file = fopen("input.txt", "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(filesize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, filesize, file);
    buffer[bytesRead] = '\0'; // Null-terminate for safety

    unsigned int checksum = calculate_checksum(buffer, bytesRead);

    printf("Bytes read: %zu\n", bytesRead);
    printf("Checksum: %u\n", checksum);

    free(buffer);
    fclose(file);

    return EXIT_SUCCESS;
}