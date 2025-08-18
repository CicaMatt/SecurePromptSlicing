#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    FILE *file;
    file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    fclose(file);

    if (chmod("secret.txt", S_IRUSR | S_IWUSR)) {
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }

    struct stat fileStat;
    if (stat("secret.txt", &fileStat) < 0) {
        perror("Failed to get file stats");
        return EXIT_FAILURE;
    }

    printf("Permissions: %o\n", fileStat.st_mode & 0777);

    return EXIT_SUCCESS;
}