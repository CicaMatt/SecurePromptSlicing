#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOAD_DIR "uploads/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s%s", UPLOAD_DIR, argv[1]);

    FILE *dest = fopen(dest_path, "wb");
    if (!dest) {
        perror("Failed to open destination file");
        fclose(src);
        return EXIT_FAILURE;
    }

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File uploaded successfully to %s\n", dest_path);
    return EXIT_SUCCESS;
}