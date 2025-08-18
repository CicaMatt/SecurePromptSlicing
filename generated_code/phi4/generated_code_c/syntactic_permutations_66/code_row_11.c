#include <stdio.h>
#include <stdlib.h>

// Dummy function to simulate processing of PDF files
void processPDF(const char* filename) {
    printf("Processing PDF file: %s\n", filename);
    // Simulate some work being done on the PDF file
}

int main() {
    const char *pdfFilename = "example.pdf";

    // Check if the file exists and is accessible
    FILE *file = fopen(pdfFilename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", pdfFilename);
        return EXIT_FAILURE;
    }
    fclose(file);

    // Process the PDF file
    processPDF(pdfFilename);

    printf("Finished processing.\n");

    return 0;
}


This C program simulates a web app's backend functionality for accepting and processing a PDF file. It checks if the file exists and then processes it using a dummy function.