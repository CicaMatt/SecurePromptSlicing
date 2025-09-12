#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOAD_DIR "uploads/"

void upload_file(const char *filename, const unsigned char *file_content, size_t content_length) {
    char path[256];
    snprintf(path, sizeof(path), "%s%s", UPLOAD_DIR, filename);
    
    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    fwrite(file_content, 1, content_length, fp);
    fclose(fp);
}