#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "secret.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    // Change the permissions of the file to read-only for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf("File created: %s\n", filename);
    return EXIT_SUCCESS;
}