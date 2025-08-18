#include <stdio.h>
#include <stdint.h>

uint32_t calculate_checksum(const uint8_t *buffer, size_t length) {
    uint32_t checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    const char *filename = "file.txt";
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t *buffer = malloc(filesize);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, filesize, file);
    fclose(file);

    uint32_t checksum = calculate_checksum(buffer, bytes_read);
    free(buffer);

    printf("Bytes read: %zu\n", bytes_read);
    printf("Checksum: %u\n", checksum);

    return 0;
}