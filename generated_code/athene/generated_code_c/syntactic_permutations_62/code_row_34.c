#include <stdio.h>
#include <stdlib.h>

unsigned short calculate_checksum(const char *buffer, size_t length) {
    unsigned short sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += (unsigned char) buffer[i];
    }
    return sum;
}

int main() {
    FILE *file = fopen("input.txt", "rb");
    if (!file) return 1;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';

    unsigned short checksum = calculate_checksum(buffer, bytes_read);

    FILE *output = fopen("output.txt", "w");
    if (output) {
        fprintf(output, "%zu %hu\n", bytes_read, checksum);
        fclose(output);
    }

    free(buffer);
    fclose(file);

    return 0;
}