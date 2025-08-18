#include <stdio.h>
#include <stdlib.h>

unsigned short calculate_checksum(const char *buffer, size_t length) {
    unsigned short sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += (unsigned char)buffer[i];
    }
    return sum;
}

int main() {
    const char *filename = "input.txt";
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char buffer[4096];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    unsigned short checksum = calculate_checksum(buffer, bytesRead);

    FILE *output = fopen("output.txt", "w");
    if (!output) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(output, "%zu %hu\n", bytesRead, checksum);
    fclose(output);

    return EXIT_SUCCESS;
}