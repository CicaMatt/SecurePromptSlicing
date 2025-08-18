#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_file_upload(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    FILE *out_file = fopen("uploaded_file", "wb");
    if (out_file == NULL) {
        perror("Failed to create output file");
        fclose(file);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, out_file);
    }

    if (ferror(file)) {
        perror("Error reading from input file");
    } else if (ferror(out_file)) {
        perror("Error writing to output file");
    }

    fclose(file);
    fclose(out_file);
}

int main() {
    const char* filename = "example.txt"; // Replace with the path of your test file
    handle_file_upload(filename);

    return 0;
}