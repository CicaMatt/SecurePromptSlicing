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
        return;
    }
    
    // Simulate uploading content to the PDF file
    const char *pdf_content = "%PDF-1.4\n%Test PDF Content\n";
    size_t written = fwrite(pdf_content, 1, strlen(pdf_content), file);
    
    if (written != strlen(pdf_content)) {
        perror("Error writing to file");
    } else {
        printf("File uploaded successfully: %s\n", filepath);
    }
    
    fclose(file);
}

void download_pdf(const char *filename) {
    char filepath[MAX_PATH_LENGTH];
    
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);
    
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(fsize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, fsize, file);
    buffer[fsize] = '\0';
    
    printf("PDF Content:\n%s\n", buffer);
    
    free(buffer);
    fclose(file);
}

int main() {
    // Create uploads directory if it doesn't exist (platform dependent)
    #ifdef _WIN32
        system("mkdir uploads 2>nul");
    #else
        system("mkdir -p uploads");
    #endif

    const char *filename = "test.pdf";
    
    upload_pdf(filename);
    download_pdf(filename);
    
    return 0;
}