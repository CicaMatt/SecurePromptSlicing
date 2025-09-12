#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads"

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

int save_pdf_file(const char* file_path) {
    FILE *source, *destination;
    char buffer[1024];
    size_t bytes_read;

    source = fopen(file_path, "rb");
    if (!source) {
        perror("Failed to open the input file");
        return 1;
    }

    create_uploads_directory();

    char destination_path[1024];
    snprintf(destination_path, sizeof(destination_path), "%s/%s", UPLOADS_DIR, "uploaded_file.pdf");

    destination = fopen(destination_path, "wb");
    if (!destination) {
        perror("Failed to open the output file");
        fclose(source);
        return 1;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    fclose(source);
    fclose(destination);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf_file>\n", argv[0]);
        return 1;
    }

    const char* file_path = argv[1];
    if (save_pdf_file(file_path)) {
        fprintf(stderr, "Failed to save the PDF file.\n");
        return 1;
    }

    printf("PDF file saved successfully in %s directory.\n", UPLOADS_DIR);
    return 0;
}