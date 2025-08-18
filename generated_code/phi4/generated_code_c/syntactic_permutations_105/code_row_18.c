#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(content, file) == EOF) {
        fclose(file);
        perror("Error writing to file");
        return EXIT_FAILURE;
    }

    fclose(file);

    // Change the permissions of the file
    struct stat file_stat;
    if (stat("secret.txt", &file_stat) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    if (chmod("secret.txt", file_stat.st_mode | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}