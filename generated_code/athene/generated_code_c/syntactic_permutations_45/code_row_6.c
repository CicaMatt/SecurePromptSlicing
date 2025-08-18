#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("safe");

    if (dir == NULL) {
        perror("Error opening directory");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return EXIT_SUCCESS;
}