#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fclose(file);

    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing permissions");
        exit(EXIT_FAILURE);
    }

    struct stat fileStat;
    if (stat("secret.txt", &fileStat) < 0) {
        perror("Error getting file stats");
        exit(EXIT_FAILURE);
    }

    printf("File Permissions: %o\n", fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return 0;
}