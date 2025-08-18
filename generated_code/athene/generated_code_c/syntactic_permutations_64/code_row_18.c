#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOAD_FOLDER "uploads/"
#define MAX_PATH 256

void upload_pdf(const char *filename) {
    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_FOLDER, filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    FILE *out = fopen(filepath, "wb");
    if (out == NULL) {
        fclose(file);
        perror("Failed to save file");
        exit(1);
    }

    char buffer[4096];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, out);
    }

    fclose(file);
    fclose(out);

    // Use filepath to download the pdf file
    printf("File uploaded and saved at: %s\n", filepath);
}

int main() {
    const char *filename = "example.pdf";
    upload_pdf(filename);
    return 0;
}