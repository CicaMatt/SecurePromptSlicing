#include <stdio.h>
#include <stdlib.h>

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

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        perror("Error allocating memory");
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Null-terminate the buffer

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    printf("Number of bytes read: %zu\n", bytes_read);
    printf("Checksum: %u\n", checksum);
    if (checksum == 0) {
        printf("The buffer is empty.\n");
    }

    free(buffer);
    fclose(file);
    return EXIT_SUCCESS;
}