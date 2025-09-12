#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "super_secret.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    // Change permissions of the file to read-only for owner
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Failed to get file stats");
        return EXIT_FAILURE;
    }
    if (chmod(filename, st.st_mode & ~S_IWGRP & ~S_IWOTH) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);
    
    return EXIT_SUCCESS;
}