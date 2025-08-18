#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fprintf(file, "%s", content);
    fclose(file);

    // Change the permissions to restrictive (owner can read and write only)
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    struct stat file_stat;
    if (stat("secret.txt", &file_stat) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    printf("Permissions: %o\n", file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return EXIT_SUCCESS;
}