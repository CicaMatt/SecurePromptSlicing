#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define PATH "/safe/"

void readDirectory(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main() {
    readDirectory(PATH);
    return 0;
}