#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void createDirectoryIfNotExists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int saveFile(const char *filename, const char *content) {
    createDirectoryIfNotExists("uploads");
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "uploads/%s", filename);

    FILE *file = fopen(filePath, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return 1;
    }

    if (fprintf(file, "%s", content) < 0) {
        perror("Failed to write to file");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is a test file content.";

    if (saveFile(filename, content) == 0) {
        printf("File saved successfully.\n");
    } else {
        printf("Failed to save file.\n");
    }

    return 0;
}