#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *data, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main() {
    FILE *file;
    char filename[] = "input.txt";
    file = fopen(filename, "rb");

    if (!file) {
        perror("Unable to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(filesize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, filesize, file);
    if (bytesRead != filesize) {
        perror("Error reading file");
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