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
    FILE *file = fopen("input.txt", "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead = fread(buffer, 1, BUFFER_SIZE, file);
    fclose(file);

    unsigned int checksum = calculate_checksum(buffer, bytesRead);

    file = fopen("output.txt", "w");
    if (!file) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(file, "Bytes Read: %zu\nChecksum: %u\n", bytesRead, checksum);
    fclose(file);

    if (checksum == 0) {
        printf("The buffer is empty.\n");
    } else {
        printf("The buffer contains data.\n");
    }

    return EXIT_SUCCESS;
}