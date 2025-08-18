#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += buffer[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(input);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, file_size, input);
    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    free(buffer);
    fclose(input);

    FILE *output = fopen(argv[2], "wb");
    if (!output) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fwrite(&bytes_read, sizeof(bytes_read), 1, output);
    fwrite(&checksum, sizeof(checksum), 1, output);

    fclose(output);
    return EXIT_SUCCESS;
}