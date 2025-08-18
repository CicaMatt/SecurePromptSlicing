#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int save_file(const char *filename, const char *content) {
    FILE *file;
    char path[256];
    snprintf(path, sizeof(path), "./uploads/%s", filename);

    create_directory("./uploads");

    file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return -1;
    }

    fprintf(file, "%s", content);
    fclose(file);

    return 0;
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is an example file.";
    
    if (save_file(filename, content) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload the file.\n");
    }
    
    return 0;
}