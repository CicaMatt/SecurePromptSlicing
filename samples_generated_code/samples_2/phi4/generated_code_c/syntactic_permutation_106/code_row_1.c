#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "super_secret.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    // Change the permissions of the file to read-only for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("The name of the file is: %s\n", filename);

    return EXIT_SUCCESS;
}