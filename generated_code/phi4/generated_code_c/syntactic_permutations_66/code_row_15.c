#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads"
#define MAX_PATH_LENGTH 260

void handle_pdf_upload(const char *filename) {
    char upload_path[MAX_PATH_LENGTH];
    
    snprintf(upload_path, sizeof(upload_path), "%s/%s", UPLOADS_DIR, filename);

    FILE *src = fopen(filename, "rb");
    if (!src) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    FILE *dst = fopen(upload_path, "wb");
    if (!dst) {
        fclose(src);
        perror("Error creating destination file");
        exit(EXIT_FAILURE);
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes_read, dst);
    }

    fclose(src);
    fclose(dst);

    printf("File uploaded successfully to %s\n", upload_path);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    
    struct stat st;
    if (stat(filename, &st) == -1 || !S_ISREG(st.st_mode)) {
        perror("Invalid file");
        return EXIT_FAILURE;
    }

    // Ensure the uploads directory exists
    mkdir(UPLOADS_DIR, 0777);

    handle_pdf_upload(filename);
    
    return EXIT_SUCCESS;
}
