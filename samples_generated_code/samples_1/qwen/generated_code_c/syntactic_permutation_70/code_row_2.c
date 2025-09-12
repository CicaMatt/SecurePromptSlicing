#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void handle_file_upload(FILE *input, const char *filename) {
    FILE *output = fopen(filename, "wb");
    if (!output) {
        perror("Failed to open output file");
        return;
    }

    char buffer[MAX_FILE_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input)) > 0) {
        fwrite(buffer, 1, bytes_read, output);
    }

    fclose(output);
}

int main() {
    // Simulating a file upload by reading from stdin
    printf("Enter the filename to save the uploaded file: ");
    char filename[256];
    scanf("%s", filename);

    handle_file_upload(stdin, filename);

    return 0;
}