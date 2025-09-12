#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secretInfo = "This is some super secret info.";
    const char *filename = "secretfile.txt";

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secretInfo);
    fclose(file);

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) { // Change permissions to read-only for owner
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    chmod(filename, st.st_mode & ~S_IWUSR);  // Make it read-only

    printf("%s\n", filename);

    return EXIT_SUCCESS;
}