#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create the file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", data);
    fclose(file);

    if (chmod(filename, 0400) < 0) {
        perror("Failed to change file permissions");
        exit(EXIT_FAILURE);
    }

    return 0;
}