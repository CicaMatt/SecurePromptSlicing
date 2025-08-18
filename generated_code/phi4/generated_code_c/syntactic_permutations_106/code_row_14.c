#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is super secret info.";
    const char *file_name = "super_secret_file.txt";

    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    // Change the permissions to read-only for the owner
    if (chmod(file_name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", file_name);

    return EXIT_SUCCESS;
}