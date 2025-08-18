#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/safe");
    if (dir == NULL) {
        perror("Failed to open directory");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && 
            strcmp(entry->d_name, "..") != 0) {
            printf("Directory: %s\n", entry->d_name);
        } else if (entry->d_type == DT_REG) {
            printf("File: %s\n", entry->d_name);
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}