#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void handle_file_upload(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }

    // Determine the size of the file
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(filesize + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read the file into buffer
    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';

    fclose(file);

    // Simulate storing the file by writing it to a new location
    char new_filename[256];
    snprintf(new_filename, sizeof(new_filename), "uploaded_%s", filename);
    FILE *new_file = fopen(new_filename, "wb");
    if (!new_file) {
        perror("Failed to open file for writing");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    fwrite(buffer, 1, filesize, new_file);
    fclose(new_file);

    printf("File '%s' uploaded successfully as '%s'.\n", filename, new_filename);

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_file_upload(argv[1]);

    return EXIT_SUCCESS;
}