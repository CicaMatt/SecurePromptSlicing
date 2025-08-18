#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOAD_DIR "uploads/"
#define MAX_FILE_SIZE 1048576 // 1MB

int save_pdf_file(const char* file_name, const unsigned char* buffer, size_t size) {
    FILE *file;
    char path[256];

    snprintf(path, sizeof(path), "%s%s", UPLOAD_DIR, file_name);

    if ((file = fopen(path, "wb")) == NULL) {
        perror("Failed to open file for writing");
        return -1;
    }

    size_t written = fwrite(buffer, 1, size, file);
    fclose(file);

    if (written != size) {
        fprintf(stderr, "Error writing to file\n");
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <filename> <file_content>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* file_name = argv[1];
    unsigned char* buffer = (unsigned char*)argv[2];
    size_t size = strlen((char*)buffer);

    if (size > MAX_FILE_SIZE) {
        fprintf(stderr, "File is too large\n");
        return EXIT_FAILURE;
    }

    if (save_pdf_file(file_name, buffer, size) != 0) {
        return EXIT_FAILURE;
    }

    printf("File saved successfully\n");
    return EXIT_SUCCESS;
}