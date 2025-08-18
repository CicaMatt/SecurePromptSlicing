#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int save_file(const char *filename, const char *content) {
    char path[256];
    snprintf(path, sizeof(path), "uploads/%s", filename);

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    fprintf(file, "%s", content);
    fclose(file);
    return 0;
}

int main() {
    create_directory("uploads");

    const char *filename = "example.txt";
    const char *content = "This is the content of the file.";

    if (save_file(filename, content) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}