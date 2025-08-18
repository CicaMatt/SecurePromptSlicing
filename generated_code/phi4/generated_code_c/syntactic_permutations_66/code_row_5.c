#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename.pdf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *uploads_dir = "./uploads";
    create_directory(uploads_dir);

    char new_path[256];
    snprintf(new_path, sizeof(new_path), "%s/%s", uploads_dir, argv[1]);

    FILE *src_file = fopen(argv[1], "rb");
    if (!src_file) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    FILE *dest_file = fopen(new_path, "wb");
    if (!dest_file) {
        perror("Error creating destination file");
        fclose(src_file);
        return EXIT_FAILURE;
    }

    const size_t buffer_size = 4096;
    char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    printf("File uploaded successfully to %s\n", new_path);
    
    return EXIT_SUCCESS;
}