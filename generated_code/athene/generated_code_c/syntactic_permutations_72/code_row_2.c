#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_FOLDER "uploads"

void create_uploads_folder() {
    if (mkdir(UPLOADS_FOLDER, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads folder");
        exit(EXIT_FAILURE);
    }
}

void upload_file(const char *filename, const char *file_content) {
    create_uploads_folder();
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_FOLDER, filename);

    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fwrite(file_content, 1, strlen(file_content), fp);
    fclose(fp);
}