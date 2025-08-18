#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define UPLOAD_DIR "./uploads"

void handle_upload(const char *filename, const char *content) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    fwrite(content, 1, strlen(content), file);
    fclose(file);
}

int main() {
    // Simulate receiving a PDF file via HTTP POST request
    const char *filename = "example.pdf";
    const char *content = "%PDF-1.4 %����\n1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n2 0 obj\n<< /Type /Pages "
                          "/Kids [3 0 R] /Count 1 >>\nendobj\n3 0 obj\n<< /Type /Page /Parent 2 0 R /Resources <<>> "
                          "/MediaBox [0 0 612 792] /Contents 4 0 R >>\nendobj\n4 0 obj\n<< /Length 55 >>\nstream\nBT"
                          "\n/F1 24 Tf\n100 700 Td\n(Hello, World!) Tj\nET\nendstream\nendobj\ntrailer\n<< /Root 1 0 R "
                          ">>\nstartxref\n120\n%%EOF";

    mkdir(UPLOAD_DIR, 0777); // Create directory if it doesn't exist

    handle_upload(filename, content);

    printf("File uploaded successfully to %s/%s\n", UPLOAD_DIR, filename);
    return 0;
}