#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (!buffer) {
        perror("malloc");
        fclose(file);
        return 1;
    }
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';

    int is_empty = (bytes_read == 0);

    fclose(file);

    const char *output_filename = "output.txt";
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("fopen");
        free(buffer);
        return 1;
    }

    fprintf(output_file, "%zu\n%d\n", bytes_read, is_empty);

    fclose(output_file);
    free(buffer);

    return 0;
}