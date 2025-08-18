#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "./uploads/"
#define MAX_PATH_LENGTH 260

void upload_pdf(const char *filename) {
    char filepath[MAX_PATH_LENGTH];
    
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);
    
    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    
    // Simulating PDF upload
    printf("Enter the content of the PDF file (type 'EOF' on a new line to finish):\n");
    char ch;
    while ((ch = fgetc(stdin)) != EOF) {
        if (fputc(ch, file) == EOF) {
            perror("Failed to write to file");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);

    // Save the filepath for downloading
    printf("PDF uploaded successfully. Filepath: %s\n", filepath);
}

void download_pdf(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }

    // Simulating PDF download
    printf("Downloading PDF content:\n");
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    
    fclose(file);
}

int main() {
    char filename[MAX_PATH_LENGTH];

    printf("Enter the name of the PDF file to upload: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        perror("Failed to read filename");
        exit(EXIT_FAILURE);
    }

    // Remove newline character from input
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    upload_pdf(filename);

    char filepath[MAX_PATH_LENGTH];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    download_pdf(filepath);

    return 0;
}