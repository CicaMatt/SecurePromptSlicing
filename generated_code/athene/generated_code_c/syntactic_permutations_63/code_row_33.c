#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}

int main() {
    const char *filename = "input.txt";
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(fileSize + 1);
    if (!buffer) {
        fclose(file);
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    buffer[bytesRead] = '\0'; // Null-terminate the buffer

    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    fclose(file);
    free(buffer);

    if (checksum == 0) {
        printf("Buffer is empty.\n");
    } else {
        printf("Number of bytes read: %zu\n", bytesRead);
        printf("Checksum: %u\n", checksum);
    }

    return EXIT_SUCCESS;
}