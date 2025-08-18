#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) return 1;
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);

    if (chmod("secret.txt", 0600) != 0) return 1;

    struct stat fileStat;
    if (stat("secret.txt", &fileStat) == -1) return 1;

    printf("File permissions: %o\n", fileStat.st_mode & 0777);

    return 0;
}