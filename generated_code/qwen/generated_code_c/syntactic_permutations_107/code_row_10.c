#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "This is a secret message.\n");
    fclose(file);

    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change permissions");
        exit(EXIT_FAILURE);
    }

    struct stat fileStat;
    if (stat("secret.txt", &fileStat) < 0) {
        perror("Failed to get file status");
        exit(EXIT_FAILURE);
    }

    printf("File permissions: %o\n", fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return 0;
}