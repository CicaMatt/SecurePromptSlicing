#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1 MB

void handle_upload(FILE* file, const char* filename) {
    FILE* destination = fopen(filename, "wb");
    if (!destination) {
        perror("Failed to open file for writing");
        return;
    }

    char buffer[BUFSIZ];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    fclose(destination);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    handle_upload(file, argv[2]);

    fclose(file);
    printf("File uploaded successfully as %s\n", argv[2]);
    return EXIT_SUCCESS;
}