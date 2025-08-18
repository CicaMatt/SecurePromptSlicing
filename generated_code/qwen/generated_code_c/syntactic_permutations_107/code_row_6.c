#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    // Create and write to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", content);
    fclose(file);

    // Change permissions of the file to restrictive (read-only for owner)
    if (chmod(filename, S_IRUSR) != 0) {
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    }

    // Print the permissions of the file
    struct stat fileStat;
    if (stat(filename, &fileStat) < 0) {
        perror("Error getting file status");
        exit(EXIT_FAILURE);
    }
    printf("File Permissions: %o\n", fileStat.st_mode & 0777);

    return 0;
}