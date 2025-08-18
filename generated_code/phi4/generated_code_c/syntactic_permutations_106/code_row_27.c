#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *info = "This is some super secret info.";
    const char *filename = "secret_info.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", info);
    fclose(file);

    // Change permissions to read-only for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("File name: %s\n", filename);

    return EXIT_SUCCESS;
}