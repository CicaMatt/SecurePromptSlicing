#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

void save_pdf(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    char upload_folder[] = "uploads/";
    char new_path[MAX_FILENAME_LENGTH];
    snprintf(new_path, sizeof(new_path), "%s%s", upload_folder, strrchr(filename, '/') + 1);

    FILE *new_file = fopen(new_path, "wb");
    if (new_file == NULL) {
        fclose(file);
        perror("Failed to create file in uploads folder");
        exit(1);
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, new_file);
    }

    fclose(file);
    fclose(new_file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_filename>\n", argv[0]);
        return 1;
    }

    save_pdf(argv[1]);
    printf("PDF file saved to uploads folder.\n");
    return 0;
}