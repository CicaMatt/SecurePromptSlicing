#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define UPLOAD_DIR "./uploads"

int create_upload_directory() {
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }
    return 0;
}

void save_file(const char *filename, const unsigned char *file_data, size_t file_size) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    fwrite(file_data, 1, file_size, fp);
    fclose(fp);
}

int main() {
    create_upload_directory();

    const char *file_path = UPLOAD_DIR "/uploaded_file.pdf";
    unsigned char dummy_pdf[] = "%PDF-1.7\n%ëì½ñ\ncatalog\n<< /Type /Catalog\n/Pages 2 0 R >>\nendobj\npages\n<< /Type /Pages\n/Kids [3 0 R]\n/Count 1 >>\nendobj\npage\n<< /Type /Page\n/Parent 2 0 R\n/MediaBox [0 0 612 792] >>\nendobj\nxref\n0 4\n0000000000 65535 f \n0000000018 00000 n \n0000000077 00000 n \n0000000124 00000 n \ntrailer\n<< /Size 4\n/Root 1 0 R >>\nstartxref\n183\n%%EOF";
    size_t dummy_pdf_size = sizeof(dummy_pdf) - 1;

    save_file(file_path, dummy_pdf, dummy_pdf_size);

    printf("File saved to %s\n", file_path);
    return 0;
}