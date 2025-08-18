#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }

    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fprintf(file, "%s", data);
    fclose(file);

    if (chmod("secret.txt", 000) != 0) {
        perror("Failed to change file permissions");
        exit(EXIT_FAILURE);
    }

    struct stat fileStat;
    if (stat("secret.txt", &fileStat) < 0) {
        perror("Failed to get file status");
        exit(EXIT_FAILURE);
    }

    printf("File Permissions: %o\n", fileStat.st_mode & 0777);

    return 0;
}