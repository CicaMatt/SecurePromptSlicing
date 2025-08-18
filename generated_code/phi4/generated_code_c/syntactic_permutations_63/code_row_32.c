#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *file;
    const char *filename = "input.txt";
    
    file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char) * filesize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, sizeof(unsigned char), filesize, file);
    
    fclose(file);

    if (bytesRead == 0) {
        printf("The buffer is empty.\n");
    } else {
        unsigned long checksum = calculate_checksum(buffer, bytesRead);
        printf("Number of bytes read: %zu\n", bytesRead);
        printf("Checksum: %lu\n", checksum);
    }

    free(buffer);

    return EXIT_SUCCESS;
}