#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += buffer[i];
    }
    return sum;
}

int main() {
    FILE *file;
    const char *filename = "input.txt";
    long file_size;
    unsigned char *buffer;
    size_t bytes_read;
    unsigned int checksum;

    file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        fclose(file);
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        free(buffer);
        fclose(file);
        perror("Failed to read file");
        return EXIT_FAILURE;
    }

    fclose(file);

    checksum = calculate_checksum(buffer, bytes_read);

    printf("Number of bytes read: %zu\n", bytes_read);
    printf("Checksum: %u\n", checksum);

    if (checksum == 0) {
        printf("The buffer is empty.\n");
    }

    free(buffer);
    return EXIT_SUCCESS;
}