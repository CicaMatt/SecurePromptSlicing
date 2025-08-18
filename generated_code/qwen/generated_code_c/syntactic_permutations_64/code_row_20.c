#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_FOLDER "uploads/"
#define MAX_FILENAME_LENGTH 256

void upload_pdf(const char *filename) {
    char source_path[MAX_FILENAME_LENGTH];
    char destination_path[MAX_FILENAME_LENGTH];

    snprintf(source_path, sizeof(source_path), "%s", filename);
    snprintf(destination_path, sizeof(destination_path), "%s%s", UPLOADS_FOLDER, filename);

    // Ensure the uploads directory exists
    FILE *dir = fopen(UPLOADS_FOLDER, "r");
    if (!dir) {
        mkdir(UPLOADS_FOLDER, 0755);
    } else {
        fclose(dir);
    }

    // Copy the file to the uploads directory
    FILE *source_file = fopen(source_path, "rb");
    FILE *destination_file = fopen(destination_path, "wb");

    if (!source_file || !destination_file) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);

    printf("File uploaded successfully to %s\n", destination_path);
}

int main() {
    // Example usage
    upload_pdf("example.pdf");

    return 0;
}