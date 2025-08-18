#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
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
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char) * fileSize);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, sizeof(unsigned char), fileSize, file);
    if (bytesRead != fileSize) {
        perror("Failed to read the complete file");
        free(buffer);
        fclose(file);
        return EXIT_FAILURE;
    }

    unsigned long checksum = calculate_checksum(buffer, bytesRead);

    printf("Checksum: %lu\n", checksum);

    free(buffer);
    fclose(file);

    return EXIT_SUCCESS;
}