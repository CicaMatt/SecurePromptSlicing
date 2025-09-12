#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

void create_directory(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int save_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return -1;
    }

    fprintf(file, "%s", content);

    fclose(file);
    return 0;
}

int upload_file(const char *filename, const char *content) {
    const char *uploads_dir = "uploads";
    
    create_directory(uploads_dir);
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", uploads_dir, filename);

    if (save_file(path, content) != 0) {
        return -1;
    }

    return 0;
}

int main() {
    const char *filename = "testfile.txt";
    const char *content = "This is a test file.";

    if (upload_file(filename, content) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
    }

    return 0;
}