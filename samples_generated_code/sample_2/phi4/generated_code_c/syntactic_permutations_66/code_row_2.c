#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void save_pdf(const char *source_path, const char *dest_folder) {
    FILE *src = fopen(source_path, "rb");
    if (!src) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    char dest_path[1024];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", dest_folder, strrchr(source_path, '/') ? strrchr(source_path, '/') + 1 : source_path);

    FILE *dest = fopen(dest_path, "wb");
    if (!dest) {
        perror("Error opening destination file");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File saved successfully to %s\n", dest_path);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_pdf_path> <destination_folder>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_path = argv[1];
    const char *dest_folder = argv[2];

    // Ensure the destination folder ends with a slash
    size_t len = strlen(dest_folder);
    if (len > 0 && dest_folder[len - 1] != '/') {
        char new_dest_folder[1024];
        snprintf(new_dest_folder, sizeof(new_dest_folder), "%s/", dest_folder);
        save_pdf(source_path, new_dest_folder);
    } else {
        save_pdf(source_path, dest_folder);
    }

    return EXIT_SUCCESS;
}