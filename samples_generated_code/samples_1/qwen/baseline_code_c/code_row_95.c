#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is super secret info.";
    const char *filename = "super_secret.txt";
    FILE *file;

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create the file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s\n", secret_info);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);

    return EXIT_SUCCESS;
}