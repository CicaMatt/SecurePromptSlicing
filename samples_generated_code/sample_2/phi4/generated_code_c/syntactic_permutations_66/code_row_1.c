#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void save_pdf(const char *filename, const char *content) {
    FILE *file = fopen("uploads/" filename, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fwrite(content, sizeof(char), strlen(content), file);

    fclose(file);
}

int main() {
    // Simulating a PDF content received from a web app
    const char *pdfContent = "%PDF-1.4\n% ... (rest of the PDF content) ...\n%%EOF";
    
    save_pdf("received_document.pdf", pdfContent);

    printf("PDF file saved successfully.\n");

    return 0;
}