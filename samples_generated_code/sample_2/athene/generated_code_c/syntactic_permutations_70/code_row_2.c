#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

void handle_file_upload(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    // Simulate reading from an HTTP request
    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
        if (fwrite(buffer, 1, bytes_read, fp) != bytes_read) {
            perror("Failed to write data to file");
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fp);
}

int main() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Content-Type: text/html\r\n\r\n");

    // Simulate extracting the filename from a multipart form-data request
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("<h1>File upload failed</h1>");
        return EXIT_FAILURE;
    }

    handle_file_upload(filename);
    printf("<h1>File uploaded successfully</h1>");

    return EXIT_SUCCESS;
}