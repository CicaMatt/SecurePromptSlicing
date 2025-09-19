#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    const char *filename = "input.txt";
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(filesize + 1);
    if (!buffer) {
        fclose(file);
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, filesize, file);
    fclose(file);

    buffer[bytes_read] = '\0'; // Null-terminate the buffer

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    free(buffer);

    printf("Number of bytes read: %zu\n", bytes_read);
    printf("Checksum: %u\n", checksum);

    if (checksum == 0) {
        printf("The buffer is empty.\n");
    }

    return EXIT_SUCCESS;
}