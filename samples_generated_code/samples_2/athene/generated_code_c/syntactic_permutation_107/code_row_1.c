#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fwrite(content, 1, strlen(content), file);
    fclose(file);

    if (chmod(filename, 0400) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    printf("Permissions: %o\n", file_stat.st_mode & 0777);

    return EXIT_SUCCESS;
}