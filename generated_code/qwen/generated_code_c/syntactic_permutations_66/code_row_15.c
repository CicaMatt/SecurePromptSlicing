#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

int save_pdf_file(const char *filename) {
    FILE *source, *destination;
    char destination_path[MAX_FILENAME_LENGTH];

    // Construct the full path for the destination file
    snprintf(destination_path, sizeof(destination_path), "%s%s", UPLOADS_DIR, filename);

    // Open the source PDF file in read binary mode
    source = fopen(filename, "rb");
    if (!source) {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination PDF file in write binary mode
    destination = fopen(destination_path, "wb");
    if (!destination) {
        perror("Error opening destination file");
        fclose(source);
        return 1;
    }

    // Copy contents from source to destination
    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytes_read, destination) != bytes_read) {
            perror("Error writing to destination file");
            fclose(source);
            fclose(destination);
            return 1;
        }
    }

    // Close both files
    fclose(source);
    fclose(destination);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Ensure the uploads directory exists
    if (mkdir(UPLOADS_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Error creating uploads directory");
        return 1;
    }

    // Save the PDF file to the uploads directory
    if (save_pdf_file(argv[1])) {
        fprintf(stderr, "Failed to save PDF file\n");
        return 1;
    }

    printf("PDF file saved successfully\n");
    return 0;
}