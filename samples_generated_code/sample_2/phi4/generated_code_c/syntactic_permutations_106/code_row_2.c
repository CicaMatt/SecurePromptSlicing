#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "super_secret_info.txt";
    const char *info = "This is some super secret info.";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", info);
    fclose(file);

    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        exit(EXIT_FAILURE);
    }

    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", filename);

    return 0;
}