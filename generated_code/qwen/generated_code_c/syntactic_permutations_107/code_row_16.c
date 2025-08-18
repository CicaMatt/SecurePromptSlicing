#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating the file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", content);
    fclose(file);

    if (chmod(filename, 0) != 0) {
        perror("Error changing permissions of the file");
        exit(EXIT_FAILURE);
    }

    return 0;
}