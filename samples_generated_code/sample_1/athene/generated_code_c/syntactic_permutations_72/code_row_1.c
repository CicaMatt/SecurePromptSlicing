#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *filename) {
    FILE *fp;
    char path[256];
    snprintf(path, sizeof(path), "./uploads/%s", filename);

    create_directory("./uploads");

    fp = fopen(path, "w");
    if (fp == NULL) {
        return -1; // Error opening file
    }

    fclose(fp);
    return 0; // Success
}