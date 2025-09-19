#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UPLOAD_DIR "uploads"
#define MAX_FILENAME_LEN 256

void save_pdf(const char *filename) {
    char path[MAX_FILENAME_LEN];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);
    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    // Simulate receiving data from web app
    const char *data = "This is a placeholder for PDF binary data";
    fwrite(data, 1, strlen(data), file);
    fclose(file);
}

int main() {
    if (mkdir(UPLOAD_DIR, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        exit(EXIT_FAILURE);
    }
    const char *filename = "example.pdf";
    save_pdf(filename);
    printf("PDF file saved successfully.\n");
    return 0;
}