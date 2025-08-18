#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define UPLOADS_DIR "./uploads"

void create_directory(const char *dir) {
    struct stat st = {0};

    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path-to-pdf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pdf_path = argv[1];

    // Check if the file exists
    struct stat buffer;
    if (stat(pdf_path, &buffer) != 0) {
        perror("File not found");
        return EXIT_FAILURE;
    }

    create_directory(UPLOADS_DIR);

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", UPLOADS_DIR, strrchr(pdf_path, '/') ? strrchr(pdf_path, '/') + 1 : pdf_path);

    // Copy the file to the uploads directory
    FILE *src = fopen(pdf_path, "rb");
    if (src == NULL) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    FILE *dest = fopen(dest_path, "wb");
    if (dest == NULL) {
        fclose(src);
        perror("Failed to open destination file");
        return EXIT_FAILURE;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File uploaded successfully to %s\n", dest_path);

    return EXIT_SUCCESS;
}