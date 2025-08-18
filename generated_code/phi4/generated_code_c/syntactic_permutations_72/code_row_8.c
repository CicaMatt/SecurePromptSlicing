#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

void create_directory(const char *path) {
    struct stat st = {0};
    
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *src_filename = argv[1];
    const char *dest_dir = "uploads";
    char dest_path[PATH_MAX];

    create_directory(dest_dir);

    snprintf(dest_path, sizeof(dest_path), "%s/%s", dest_dir, src_filename);

    FILE *src_file = fopen(src_filename, "rb");
    if (!src_file) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    FILE *dest_file = fopen(dest_path, "wb");
    if (!dest_file) {
        perror("Error creating destination file");
        fclose(src_file);
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    if (ferror(src_file)) {
        perror("Error reading source file");
        fclose(src_file);
        fclose(dest_file);
        return EXIT_FAILURE;
    }

    fclose(src_file);
    fclose(dest_file);

    printf("File uploaded successfully to %s\n", dest_path);

    return EXIT_SUCCESS;
}