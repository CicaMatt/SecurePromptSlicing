#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    fclose(file);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);
    
    if (checksum == 0) {
        FILE *output_file = fopen("result.txt", "w");
        if (!output_file) {
            perror("Error opening output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fprintf(output_file, "Bytes Read: %zu\nChecksum: %u\n", bytes_read, checksum);
        fclose(output_file);
    } else {
        printf("Checksum is not zero.\n");
    }

    free(buffer);
    return 0;
}