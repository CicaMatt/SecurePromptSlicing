#include <stdio.h>
#include <string.h>

#define MAX_PATH 256

void upload_pdf(const char *filename) {
    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);
    
    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Failed to save PDF file");
        return;
    }
    fclose(file);

    // Simulate downloading the file using the filepath
    printf("Downloading PDF from: %s\n", filepath);
}

int main() {
    const char *user_uploaded_filename = "example.pdf";
    upload_pdf(user_uploaded_filename);
    return 0;
}