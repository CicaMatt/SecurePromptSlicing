#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void create_directory(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int save_file_to_directory(const char *filename, const char *source_path, const char *destination_dir) {
    FILE *src, *dest;
    char full_dest_path[1024];

    snprintf(full_dest_path, sizeof(full_dest_path), "%s/%s", destination_dir, filename);

    src = fopen(source_path, "rb");
    if (!src) {
        perror("Failed to open source file");
        return -1;
    }

    dest = fopen(full_dest_path, "wb");
    if (!dest) {
        fclose(src);
        perror("Failed to create destination file");
        return -1;
    }

    char buffer[4096];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file_path> <filename>\n", argv[0]);
        return 1;
    }

    const char *uploads_dir = "./uploads";
    create_directory(uploads_dir);

    int result = save_file_to_directory(argv[2], argv[1], uploads_dir);
    if (result != 0) {
        fprintf(stderr, "Failed to upload file\n");
        return 1;
    }

    printf("File uploaded successfully!\n");

    return 0;
}