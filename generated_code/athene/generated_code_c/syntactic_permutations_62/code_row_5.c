#include <stdio.h>
#include <stdlib.h>

unsigned short checksum(const char *buffer, int length) {
    unsigned short sum = 0;
    for (int i = 0; i < length; i++) {
        sum += (unsigned char)buffer[i];
    }
    return sum;
}

int main() {
    const int bufferSize = 1024;
    char buffer[bufferSize];
    FILE *input = fopen("input.txt", "rb");
    if (!input) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, bufferSize, input);
    fclose(input);

    unsigned short cs = checksum(buffer, bytesRead);

    FILE *output = fopen("output.txt", "w");
    if (!output) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(output, "%zu %hu\n", bytesRead, cs);
    fclose(output);

    return EXIT_SUCCESS;
}