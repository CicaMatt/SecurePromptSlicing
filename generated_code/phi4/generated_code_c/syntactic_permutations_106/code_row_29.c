#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "super_secret.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fputs(secret_info, file);
    fclose(file);

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Error getting file status");
        remove(filename);
        return EXIT_FAILURE;
    }

    // Change the permissions to read-only for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);

    return EXIT_SUCCESS;
}