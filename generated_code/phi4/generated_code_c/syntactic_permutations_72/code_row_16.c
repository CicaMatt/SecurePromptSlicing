#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int mkdir_if_not_exists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        if (mkdir(path, 0700) != 0 && errno != EEXIST) {
            perror("Failed to create directory");
            return -1;
        }
    }
    return 0;
}

int upload_file(const char *source_path, const char *target_dir, const char *file_name) {
    mkdir_if_not_exists(target_dir);

    char full_target_path[1024];
    snprintf(full_target_path, sizeof(full_target_path), "%s/%s", target_dir, file_name);

    FILE *src = fopen(source_path, "rb");
    if (src == NULL) {
        perror("Failed to open source file");
        return -1;
    }

    FILE *dst = fopen(full_target_path, "wb");
    if (dst == NULL) {
        perror("Failed to create target file");
        fclose(src);
        return -1;
    }

    char buffer[4096];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dst);
    }

    fclose(src);
    fclose(dst);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <source_file> <target_dir> <file_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_path = argv[1];
    const char *target_dir = argv[2];
    const char *file_name = argv[3];

    if (upload_file(source_path, target_dir, file_name) != 0) {
        fprintf(stderr, "Failed to upload file\n");
        return EXIT_FAILURE;
    }

    printf("File uploaded successfully to %s/%s\n", target_dir, file_name);
    return EXIT_SUCCESS;
}