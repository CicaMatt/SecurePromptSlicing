#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void create_uploads_folder() {
    struct stat st = {0};
    if (stat("uploads", &st) == -1) {
        mkdir("uploads", 0700);
    }
}

void upload_file(const char *filename) {
    FILE *src, *dst;
    char path[256];
    int ch;

    create_uploads_folder();
    snprintf(path, sizeof(path), "uploads/%s", filename);

    src = fopen(filename, "rb");
    if (src == NULL) return;

    dst = fopen(path, "wb");
    if (dst == NULL) {
        fclose(src);
        return;
    }

    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);
}