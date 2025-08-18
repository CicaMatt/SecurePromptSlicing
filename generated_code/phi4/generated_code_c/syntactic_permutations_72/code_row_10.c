#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads"

void ensure_directory_exists(const char *dir) {
    FILE *fp = fopen(dir, "a");
    if (fp == NULL) {
        mkdir(dir, 0777);
    }
    fclose(fp);
}

int upload_file(const char *filename, const char *content) {
    char filepath[256];
    
    ensure_directory_exists(UPLOADS_DIR);

    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOADS_DIR, filename);
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return -1;
    }

    if (fputs(content, file) == EOF) {
        fclose(file);
        perror("Error writing to file");
        return -1;
    }
    
    fclose(file);
    printf("File uploaded successfully: %s\n", filepath);
    return 0;
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is an example file content.";
    
    if (upload_file(filename, content) != 0) {
        fprintf(stderr, "Failed to upload file.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}