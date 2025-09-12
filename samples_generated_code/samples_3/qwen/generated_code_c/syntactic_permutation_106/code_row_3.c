#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    char *secret_info = "This is super secret info.";
    const char *filename = "super_secret.txt";
    FILE *file;

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Error changing file permissions to read-only for the owner");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);

    return EXIT_SUCCESS;
}