#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    FILE *file = fopen(file_path, "rb");

    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (fstat(fileno(file), &st) != 0) {
        perror("Error getting file size");
        fclose(file);
        return EXIT_FAILURE;
    }

    unsigned char *buffer = malloc(st.st_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, st.st_size, file);

    // Example of handling the binary data (e.g., printing hex representation)
    for (size_t i = 0; i < st.st_size; ++i) {
        printf("%02x ", buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }

    free(buffer);
    fclose(file);

    return EXIT_SUCCESS;
}