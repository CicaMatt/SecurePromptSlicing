#include <stdio.h>
#include <stdlib.h>

unsigned char calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned char sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += buffer[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(filesize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, filesize, file);
    fclose(file);

    if (bytes_read != filesize) {
        fprintf(stderr, "Failed to read file\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    unsigned char checksum = calculate_checksum(buffer, bytes_read);

    printf("Number of bytes read: %zu\n", bytes_read);
    printf("Checksum: %u\n", checksum);

    if (checksum == 0) {
        printf("The buffer is empty.\n");
    }

    free(buffer);
    return EXIT_SUCCESS;
}