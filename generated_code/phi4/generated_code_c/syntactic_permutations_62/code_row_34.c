#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

unsigned int calculate_checksum(const unsigned char *data, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main() {
    FILE *file_in = fopen("input_file.txt", "rb");
    FILE *file_out = fopen("output_file.txt", "w");

    if (!file_in || !file_out) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file_in)) > 0) {
        unsigned int checksum = calculate_checksum(buffer, bytes_read);

        if (checksum == 0 && bytes_read != 0) {
            fprintf(file_out, "Buffer is empty\n");
        } else {
            fprintf(file_out, "Bytes read: %zu\n", bytes_read);
            fprintf(file_out, "Checksum: %u\n", checksum);
        }
    }

    fclose(file_in);
    fclose(file_out);

    return 0;
}