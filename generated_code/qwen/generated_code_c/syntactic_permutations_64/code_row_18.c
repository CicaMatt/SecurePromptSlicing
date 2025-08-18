#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_FOLDER "uploads/"
#define MAX_FILENAME_LENGTH 256

void upload_pdf(const char* filename) {
    FILE *source, *destination;
    char source_path[MAX_FILENAME_LENGTH];
    char destination_path[MAX_FILENAME_LENGTH];

    // Construct full file paths
    snprintf(source_path, sizeof(source_path), "%s", filename);
    snprintf(destination_path, sizeof(destination_path), "%s%s", UPLOADS_FOLDER, filename);

    // Open the source file in read mode
    source = fopen(source_path, "rb");
    if (!source) {
        perror("Error opening source file");
        return;
    }

    // Create and open the destination file in write mode
    destination = fopen(destination_path, "wb");
    if (!destination) {
        perror("Error opening destination file");
        fclose(source);
        return;
    }

    // Copy contents from source to destination
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }

    // Close files
    fclose(source);
    fclose(destination);

    printf("File uploaded successfully to %s\n", destination_path);
}

void download_pdf(const char* filename) {
    FILE *source;
    char filepath[MAX_FILENAME_LENGTH];

    // Construct full file path
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_FOLDER, filename);

    // Open the source file in read mode
    source = fopen(filepath, "rb");
    if (!source) {
        perror("Error opening file for download");
        return;
    }

    printf("File downloaded successfully from %s\n", filepath);
    fclose(source);
}

int main() {
    const char* filename = "example.pdf";

    // Simulate uploading a PDF
    upload_pdf(filename);

    // Simulate downloading the uploaded PDF
    download_pdf(filename);

    return 0;
}