#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);

    if (chmod("secret.txt", 0000) != 0) {
        perror("Failed to change file permissions");
        exit(EXIT_FAILURE);
    }

    return 0;
}