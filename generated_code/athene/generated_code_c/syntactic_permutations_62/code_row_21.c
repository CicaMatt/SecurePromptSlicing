#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = malloc(fileSize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        perror("fread");
        free(buffer);
        fclose(file);
        return EXIT_FAILURE;
    }

    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    free(buffer);
    fclose(file);

    if (checksum == 0) {
        printf("Checksum is 0\n");
    } else {
        printf("Checksum is not 0: %u\n", checksum);
    }

    return EXIT_SUCCESS;
}