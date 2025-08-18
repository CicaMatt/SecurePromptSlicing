#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>  // For directory operations

void read_safe_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("Directory: %s\n", entry->d_name);
            read_safe_directory(path "/" ENTRY_NAME(entry));
        } else if (entry->d_type == DT_REG) {
            printf("File: %s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main() {
    const char *safe_path = "/path/to/safe/directory"; // Replace with your safe directory path
    read_safe_directory(safe_path);
    return 0;
}