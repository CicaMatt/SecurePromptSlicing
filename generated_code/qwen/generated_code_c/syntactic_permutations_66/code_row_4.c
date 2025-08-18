#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads"
#define MAX_FILENAME_LENGTH 256

int save_pdf_file(const char* filename) {
    FILE *source, *destination;
    char destination_path[MAX_FILENAME_LENGTH];

    snprintf(destination_path, sizeof(destination_path), "%s/%s", UPLOADS_DIR, filename);

    source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open the source file");
        return 1;
    }

    destination = fopen(destination_path, "wb");
    if (!destination) {
        perror("Failed to create the destination file");
        fclose(source);
        return 1;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    if (ferror(source)) {
        perror("Failed to read from the source file");
        fclose(source);
        fclose(destination);
        return 1;
    }

    fclose(source);
    fclose(destination);

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];

    // Check if the uploads directory exists or create it
    if (mkdir(UPLOADS_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        return 1;
    }

    if (save_pdf_file(filename)) {
        fprintf(stderr, "Failed to save the PDF file\n");
        return 1;
    }

    printf("PDF file saved successfully in %s/%s\n", UPLOADS_DIR, filename);

    return 0;
}