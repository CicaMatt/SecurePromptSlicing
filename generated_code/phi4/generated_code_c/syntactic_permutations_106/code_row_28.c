#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret information.";
    const char *filename = "super_secret.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf("File created: %s\n", filename);

    return EXIT_SUCCESS;
}