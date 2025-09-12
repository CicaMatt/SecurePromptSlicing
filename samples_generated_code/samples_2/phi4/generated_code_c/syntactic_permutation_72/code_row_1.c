#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void upload_file(const char *filename, const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char uploads_dir[256];
    snprintf(uploads_dir, sizeof(uploads_dir), "%s/%s", "uploads", filename);

    FILE *upload_file = fopen(uploads_dir, "wb");
    if (upload_file == NULL) {
        perror("Error creating file in upload directory");
        fclose(file);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, upload_file);
    }

    fclose(file);
    fclose(upload_file);

    printf("File uploaded successfully to %s\n", uploads_dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <filepath>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *filepath = argv[2];

    upload_file(filename, filepath);

    return EXIT_SUCCESS;
}