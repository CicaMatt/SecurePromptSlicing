#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "Super Secret Info";
    const char *filename = "secret.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fputs(secret_info, file);
    fclose(file);

    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }
    
    // Change permissions to read-only for the owner
    if (chmod(filename, st.st_mode & ~S_IWGRP & ~S_IWOTH & S_IRUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf("Super secret info written to %s and file permissions changed.\n", filename);
    
    return EXIT_SUCCESS;
}