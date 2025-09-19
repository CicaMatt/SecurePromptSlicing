#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void handle_request(const char *file_path, const char *upload_dir) {
    FILE *pdf_file = fopen(file_path, "rb");
    if (!pdf_file) {
        perror("Failed to open file");
        return;
    }

    // Ensure upload directory exists
    mkdir(upload_dir, 0777);

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", upload_dir, strrchr(file_path, '/') ? strrchr(file_path, '/') + 1 : file_path);
    
    FILE *dest_file = fopen(dest_path, "wb");
    if (!dest_file) {
        perror("Failed to open destination file");
        fclose(pdf_file);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, pdf_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(dest_file);
    fclose(pdf_file);

    printf("File uploaded successfully to %s\n", dest_path);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file_path> <upload_dir>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1], argv[2]);

    return EXIT_SUCCESS;
}