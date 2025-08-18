#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"

void upload_image(const char* filename, const char* output_filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(filesize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, 1, filesize, file);
    fclose(file);
    if (bytes_read != filesize) {
        perror("Failed to read file");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    buffer[filesize] = '\0';

    // Calculate the length of the base64 encoded string
    size_t encoded_length = Base64encode_len(bytes_read);

    char* encoded_string = (char*)malloc(encoded_length + 1);
    if (!encoded_string) {
        perror("Memory allocation failed");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    Base64encode(encoded_string, (const char*)buffer, bytes_read);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        free(encoded_string);
        exit(EXIT_FAILURE);
    }

    fprintf(output_file, "%s", encoded_string);
    fclose(output_file);

    free(buffer);
    free(encoded_string);
}

int main() {
    upload_image("input.jpg", "output.txt");
    return 0;
}