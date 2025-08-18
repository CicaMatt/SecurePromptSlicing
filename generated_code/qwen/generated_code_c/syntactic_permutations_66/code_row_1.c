#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define UPLOADS_DIR "uploads/"

int saveFileToUploads(const char* filename, const char* content) {
    char fullPath[MAX_FILENAME_LENGTH];
    snprintf(fullPath, sizeof(fullPath), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(fullPath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return 1;
    }

    size_t contentLength = strlen(content);
    if (fwrite(content, 1, contentLength, file) != contentLength) {
        perror("Failed to write to file");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

int main() {
    const char* filename = "example.pdf";
    const char* pdfContent = "%PDF-1.4\n...\n%%EOF"; // Simplified PDF content

    if (saveFileToUploads(filename, pdfContent)) {
        fprintf(stderr, "Failed to save file %s\n", filename);
        return EXIT_FAILURE;
    }

    printf("File %s saved successfully in %s directory.\n", filename, UPLOADS_DIR);
    return EXIT_SUCCESS;
}