#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define UPLOAD_DIR "uploads"

int save_pdf(const char *filename) {
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        if (mkdir(UPLOAD_DIR, 0755) != 0) {
            perror("Failed to create directory");
            return 1;
        }
    }

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", UPLOAD_DIR, filename);

    FILE *source = fopen(filename, "rb");
    if (source == NULL) {
        perror("Failed to open source file");
        return 1;
    }

    FILE *dest = fopen(dest_path, "wb");
    if (dest == NULL) {
        fclose(source);
        perror("Failed to open destination file");
        return 1;
    }

    char buffer[4096];
    size_t nread;
    while ((nread = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, nread, dest) != nread) {
            fclose(source);
            fclose(dest);
            perror("Failed to write file");
            return 1;
        }
    }

    fclose(source);
    fclose(dest);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    if (save_pdf(filename) == 0) {
        printf("PDF saved successfully.\n");
    } else {
        printf("Failed to save PDF.\n");
    }
    return 0;
}