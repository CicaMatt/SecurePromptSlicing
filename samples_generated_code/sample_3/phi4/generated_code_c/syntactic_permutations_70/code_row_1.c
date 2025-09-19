#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int upload_file(const char *filename, const unsigned char *data, size_t data_size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    size_t written = fwrite(data, 1, data_size, file);
    fclose(file);

    if (written != data_size) {
        perror("Error writing file");
        return -1;
    }

    return 0;
}

int main(void) {
    const char *filename = "uploads/test.txt";
    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;

    // Simulate reading a file
    FILE *input_file = fopen("test_input.txt", "rb");
    if (input_file == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, input_file)) > 0) {
        if (upload_file(filename, buffer, bytes_read) != 0) {
            fprintf(stderr, "Failed to upload file\n");
            fclose(input_file);
            return EXIT_FAILURE;
        }
    }

    fclose(input_file);
    printf("File uploaded successfully.\n");

    return EXIT_SUCCESS;
}