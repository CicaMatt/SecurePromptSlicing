#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secretInfo = "This is some super secret information.";
    const char *filename = "secret.txt";
    FILE *file;

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", secretInfo);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", filename);

    return 0;
}