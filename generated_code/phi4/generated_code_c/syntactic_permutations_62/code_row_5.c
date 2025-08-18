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
    FILE *inputFile = fopen("input.bin", "rb");
    if (!inputFile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    unsigned char buffer[BUFFER_SIZE] = {0};
    size_t bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile);
    fclose(inputFile);

    unsigned int checksum = calculate_checksum(buffer, bytesRead);

    FILE *outputFile = fopen("checksum_info.txt", "w");
    if (!outputFile) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Bytes Read: %zu\nChecksum: %u\n", bytesRead, checksum);
    fclose(outputFile);

    printf("Number of bytes read and checksum saved to 'checksum_info.txt'\n");

    if (checksum == 0) {
        printf("The buffer is empty.\n");
    } else {
        printf("Buffer is not empty. Checksum: %u\n", checksum);
    }

    return EXIT_SUCCESS;
}