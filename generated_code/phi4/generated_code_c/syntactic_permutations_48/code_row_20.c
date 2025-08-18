#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void img(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    img(argv[1]);

    return EXIT_SUCCESS;
}