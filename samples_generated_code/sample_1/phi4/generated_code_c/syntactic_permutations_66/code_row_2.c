#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOAD_DIR "uploads/"
#define MAX_PATH_LENGTH 256

void save_pdf(const char *filename, const char *pdf_data) {
    FILE *file;
    char filepath[MAX_PATH_LENGTH];
    
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);
    
    // Ensure the uploads directory exists
    mkdir(UPLOAD_DIR, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

    file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fwrite(pdf_data, sizeof(char), strlen(pdf_data), file);
    
    fclose(file);
}

int main() {
    const char *pdf_filename = "document.pdf";
    const char *pdf_content = "%PDF-1.4\n% ... PDF content here ...\n%%EOF";

    save_pdf(pdf_filename, pdf_content);

    printf("PDF saved successfully.\n");

    return 0;
}