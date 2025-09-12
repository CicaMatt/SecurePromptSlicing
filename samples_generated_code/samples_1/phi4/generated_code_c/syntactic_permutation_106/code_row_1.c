#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "Super Secret Info";
    const char *filename = "super_secret.txt";

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    // Change permissions to read-only for owner
    if (chmod(filename, st.st_mode & ~S_IWUSR) == -1) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);

    return EXIT_SUCCESS;
}