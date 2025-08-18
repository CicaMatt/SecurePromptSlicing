#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_FOLDER "uploads"

void create_uploads_folder() {
    if (mkdir(UPLOADS_FOLDER, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create uploads folder");
        exit(EXIT_FAILURE);
    }
}

void upload_file(const char *filename, const char *content) {
    create_uploads_folder();

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_FOLDER, filename);

    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fwrite(content, 1, strlen(content), file);
    fclose(file);
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is the content of the uploaded file.";
    upload_file(filename, content);

    return 0;
}