#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to create file");
        return 1;
    }
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);

    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change permissions");
        return 1;
    }

    struct stat fileStat;
    if (stat("secret.txt", &fileStat) < 0) {
        perror("Failed to get file information");
        return 1;
    }

    printf("Permissions: %o\n", fileStat.st_mode & 0777);

    return 0;
}