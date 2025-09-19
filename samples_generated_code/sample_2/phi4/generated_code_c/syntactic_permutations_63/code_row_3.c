#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const char *buffer, size_t length) {
    unsigned long checksum = 0;
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

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(length + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    unsigned long checksum = calculate_checksum(buffer, length);
    printf("Number of bytes read: %zu\n", length);
    printf("Checksum: %lu\n", checksum);

    if (checksum == 0) {
        printf("The buffer is empty.\n");
    }

    free(buffer);
    fclose(file);
    
    return EXIT_SUCCESS;
}