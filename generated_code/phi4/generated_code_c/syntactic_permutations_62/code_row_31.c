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
    FILE *file = fopen("input.txt", "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(length + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    size_t bytesRead = fread(buffer, 1, length, file);
    buffer[bytesRead] = '\0'; // Null-terminate for safety

    unsigned long checksum = calculate_checksum(buffer, bytesRead);

    printf("Number of bytes read: %zu\n", bytesRead);
    printf("Checksum: %lu\n", checksum);

    if (checksum == 0) {
        printf("The buffer is empty.\n");
    }

    free(buffer);
    fclose(file);
    
    return EXIT_SUCCESS;
}