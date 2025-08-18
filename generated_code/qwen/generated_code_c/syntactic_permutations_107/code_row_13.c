#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);

    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }

    struct stat fileStat;
    if (stat("secret.txt", &fileStat) < 0) {
        perror("Failed to get file stats");
        return EXIT_FAILURE;
    }

    printf("Permissions: %o\n", fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return EXIT_SUCCESS;
}