#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += buffer[i];
    }
    return sum % 256;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(size + 1);
    if (!buffer) {
        fclose(file);
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, 1, size, file);
    fclose(file);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    free(buffer);

    printf("Number of bytes read: %zu\n", bytes_read);
    printf("Checksum: %u\n", checksum);

    if (checksum == 0) {
        printf("The buffer is empty.\n");
    }

    return EXIT_SUCCESS;
}