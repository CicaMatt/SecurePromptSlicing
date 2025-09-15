#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate saving a PDF file into the "uploads" directory.
void savePdf(const char *filename, const unsigned char *pdfData, size_t dataSize) {
    // Create or open the target file in binary write mode.
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "./uploads/%s", filename);

    FILE *file = fopen(filePath, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Write the PDF data to the file.
    size_t written = fwrite(pdfData, 1, dataSize, file);
    if (written != dataSize) {
        fprintf(stderr, "Error writing file: %s\n", strerror(errno));
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Close the file.
    fclose(file);
}
