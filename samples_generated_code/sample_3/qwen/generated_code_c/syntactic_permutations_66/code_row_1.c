#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

int save_file(const char *filename, const unsigned char *buffer, size_t length) {
    FILE *file;
    char path[MAX_FILENAME_LENGTH];

    snprintf(path, sizeof(path), "%s%s", UPLOADS_DIR, filename);

    file = fopen(path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return 1;
    }

    if (fwrite(buffer, 1, length, file) != length) {
        perror("Failed to write to file");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

int main() {
    // Example usage: simulate receiving a PDF file as binary data
    const unsigned char pdf_data[] = { 
        // This is just a placeholder for binary data. In a real application, this would be the content of the uploaded PDF.
        '%', 'P', 'D', 'F', '-', '1', '.', '4', '\n'
        // Add more binary data as needed
    };
    size_t pdf_length = sizeof(pdf_data) / sizeof(pdf_data[0]);

    const char *filename = "example.pdf";

    if (save_file(filename, pdf_data, pdf_length)) {
        fprintf(stderr, "Failed to save file.\n");
        return EXIT_FAILURE;
    }

    printf("File saved successfully as %s%s\n", UPLOADS_DIR, filename);
    return EXIT_SUCCESS;
}