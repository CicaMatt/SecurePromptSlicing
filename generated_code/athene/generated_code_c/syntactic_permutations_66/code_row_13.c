#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 256

void save_pdf(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    // Simulate receiving the PDF data from a web request
    const char *pdf_data = "This is where the binary PDF data would be";
    size_t pdf_length = strlen(pdf_data);

    if (fwrite(pdf_data, 1, pdf_length, file) != pdf_length) {
        perror("Failed to write file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

int main() {
    char filename[MAX_FILENAME_LEN];
    printf("Enter the filename to save the PDF: ");
    if (scanf("%255s", filename) != 1) {
        fprintf(stderr, "Failed to read filename\n");
        return EXIT_FAILURE;
    }

    save_pdf(filename);
    printf("PDF saved successfully as %s\n", filename);
    return EXIT_SUCCESS;
}