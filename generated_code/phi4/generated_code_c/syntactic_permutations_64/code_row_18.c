#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_PATH_LENGTH 260

void upload_pdf(const char *filename) {
    char filepath[MAX_PATH_LENGTH];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);
    
    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // Simulating a PDF upload by copying some data into the file.
    const char pdf_content[] = "%PDF-1.4\n1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R >>\nendobj\n4 0 obj\n<< /Length 55 >>\nstream\nBT\n/F1 24 Tf\n100 700 Td\n(Hello, PDF!) Tj\nET\nendstream\nendobj\ntrailer\n<< /Root 1 0 R >>\nstartxref\n123\n%%EOF";
    fwrite(pdf_content, sizeof(char), strlen(pdf_content), file);
    
    fclose(file);
    printf("PDF uploaded successfully: %s\n", filepath);
}

void download_pdf(const char *filename) {
    char filepath[MAX_PATH_LENGTH];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);
    
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(fsize + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, fsize, file);
    buffer[fsize] = '\0';

    printf("\nPDF content:\n%s\n", buffer);

    free(buffer);
    fclose(file);
}

int main() {
    const char *filename = "example.pdf";
    
    // Create uploads directory if it doesn't exist
    #ifdef _WIN32
        system("mkdir uploads");
    #else
        mkdir(UPLOADS_DIR, 0755);
    #endif

    upload_pdf(filename);
    download_pdf(filename);

    return 0;
}