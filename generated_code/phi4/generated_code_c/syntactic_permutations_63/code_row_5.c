#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");

    if (!input_file || !output_file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, input_file);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    fprintf(output_file, "Bytes Read: %zu\n", bytes_read);
    fprintf(output_file, "Checksum: %u\n", checksum);

    if (checksum == 0) {
        fprintf(stdout, "The buffer is empty.\n");
    } else {
        fprintf(stdout, "The buffer is not empty.\n");
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}