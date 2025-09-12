#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UPLOAD_FOLDER "./uploads/"

void save_pdf(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char new_filename[256];
    snprintf(new_filename, sizeof(new_filename), "%s%s", UPLOAD_FOLDER, filename);

    FILE *new_file = fopen(new_filename, "wb");
    if (new_file == NULL) {
        fclose(file);
        perror("Error creating file in uploads folder");
        return;
    }

    const int buffer_size = 4096;
    char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, file)) > 0) {
        fwrite(buffer, 1, bytes_read, new_file);
    }

    fclose(file);
    fclose(new_file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf-file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    save_pdf(filename);

    printf("PDF file saved to uploads folder.\n");
    return 0;
}