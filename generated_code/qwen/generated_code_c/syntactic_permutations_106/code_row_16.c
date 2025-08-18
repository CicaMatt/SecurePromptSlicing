#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    char *secret_info = "This is super secret information.";
    FILE *file;
    const char *filename = "secret.txt";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create the file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change file permissions");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", filename);

    return 0;
}