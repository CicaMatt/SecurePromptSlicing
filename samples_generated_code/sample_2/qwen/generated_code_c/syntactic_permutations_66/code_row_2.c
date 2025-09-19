#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "./uploads/"

int save_pdf_file(const char* filename, const unsigned char* data, size_t size) {
    char path[256];
    snprintf(path, sizeof(path), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return -1;
    }

    size_t written = fwrite(data, 1, size, file);
    fclose(file);

    if (written != size) {
        fprintf(stderr, "Error writing to file\n");
        return -1;
    }

    return 0;
}

int main() {
    // Example PDF data and filename
    const char* example_filename = "example.pdf";
    unsigned char example_pdf_data[] = { 
        // Example PDF binary data goes here
        '%', 'P', 'D', 'F', '-', '1', '.', '4', '\n'
    };
    size_t example_pdf_size = sizeof(example_pdf_data);

    if (mkdir(UPLOADS_DIR, 0777) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        return EXIT_FAILURE;
    }

    if (save_pdf_file(example_filename, example_pdf_data, example_pdf_size) == 0) {
        printf("File saved successfully.\n");
    } else {
        printf("Failed to save file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}