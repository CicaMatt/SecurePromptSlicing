#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define UPLOAD_DIR "uploads"

void create_directory_if_not_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }
}

int save_pdf_file(const char *filename, const unsigned char *data, size_t data_len) {
    create_directory_if_not_exists(UPLOAD_DIR);

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    FILE *file = fopen(path, "wb");
    if (!file) {
        return -1;
    }

    fwrite(data, 1, data_len, file);
    fclose(file);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <filename> <data>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    unsigned char *data = (unsigned char *)argv[2];
    size_t data_len = strlen((const char *)data);

    if (save_pdf_file(filename, data, data_len) != 0) {
        fprintf(stderr, "Failed to save PDF file.\n");
        return 1;
    }

    printf("PDF file saved successfully.\n");
    return 0;
}