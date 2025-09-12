#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define UPLOAD_FOLDER "uploads"

int create_upload_folder() {
    struct stat st = {0};
    if (stat(UPLOAD_FOLDER, &st) == -1) {
        mkdir(UPLOAD_FOLDER, 0700);
    }
    return 1;
}

int save_file(const char *filename, const char *content, size_t content_length) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_FOLDER, filename);

    FILE *file = fopen(path, "wb");
    if (file == NULL) return 0;

    fwrite(content, 1, content_length, file);
    fclose(file);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <content>\n", argv[0]);
        return 1;
    }

    create_upload_folder();

    const char *filename = argv[1];
    const char *content = argv[2];
    size_t content_length = strlen(content);

    if (save_file(filename, content, content_length)) {
        printf("File saved successfully.\n");
    } else {
        fprintf(stderr, "Failed to save file.\n");
        return 1;
    }

    return 0;
}