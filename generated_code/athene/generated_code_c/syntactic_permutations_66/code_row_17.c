#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define DEST_FOLDER "./pdfs/"

void save_pdf(const char *file_path) {
    FILE *source = fopen(file_path, "rb");
    if (!source) {
        perror("Failed to open source file");
        exit(1);
    }

    const char *filename = strrchr(file_path, '/');
    if (!filename) filename = file_path;
    else filename++;

    char dest_path[BUFFER_SIZE];
    snprintf(dest_path, sizeof(dest_path), "%s%s", DEST_FOLDER, filename);

    FILE *dest = fopen(dest_path, "wb");
    if (!dest) {
        perror("Failed to open destination file");
        fclose(source);
        exit(1);
    }

    size_t n;
    char buffer[BUFFER_SIZE];
    while ((n = fread(buffer, 1, BUFFER_SIZE, source)) > 0) {
        fwrite(buffer, 1, n, dest);
    }

    fclose(source);
    fclose(dest);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf-file>\n", argv[0]);
        exit(1);
    }

    save_pdf(argv[1]);

    printf("PDF saved successfully.\n");
    return 0;
}