#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void upload_pdf(const char *filename);
char* download_pdf(const char *filepath);

int main() {
    const char *uploaded_file = "example.pdf";
    
    // Simulate uploading a PDF file
    upload_pdf(uploaded_file);
    
    // Simulate downloading the uploaded PDF file
    char filepath[256] = "./uploads/";
    strcat(filepath, uploaded_file);
    char* downloaded_content = download_pdf(filepath);

    if (downloaded_content != NULL) {
        printf("PDF downloaded successfully.\n");
        free(downloaded_content);
    } else {
        printf("Failed to download PDF.\n");
    }

    return 0;
}

void upload_pdf(const char *filename) {
    char filepath[256] = "./uploads/";
    strcat(filepath, filename);

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    // Simulating writing some content to the PDF
    fprintf(file, "%s uploaded successfully.\n", filename);
    fclose(file);

    printf("PDF %s has been uploaded to %s\n", filename, filepath);
}

char* download_pdf(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(sizeof(char) * (filesize + 1));
    if (content == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    fread(content, sizeof(char), filesize, file);
    content[filesize] = '\0';

    fclose(file);

    printf("PDF %s has been downloaded.\n", filepath);
    return content;
}
