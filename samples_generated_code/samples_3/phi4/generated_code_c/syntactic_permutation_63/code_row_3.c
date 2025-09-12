#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *file = fopen("input.txt", "rb");
    if (!file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(length);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, length, file);
    fclose(file);

    unsigned long checksum = calculate_checksum(buffer, length);
    int isEmpty = (checksum == 0);

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Number of bytes read: %zu\n", length);
    fprintf(output_file, "Checksum: %lu\n", checksum);
    fclose(output_file);

    free(buffer);
    
    if (isEmpty) {
        printf("The file is empty.\n");
    } else {
        printf("The file is not empty.\n");
    }

    return EXIT_SUCCESS;
}