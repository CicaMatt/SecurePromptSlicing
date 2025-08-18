#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    // Create and write to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s", content);
    fclose(file);

    // Change permissions of the file to restrictive (read-only by owner)
    if (chmod(filename, S_IRUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    // Print the permissions of the file
    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }
    printf("%o\n", (unsigned int)st.st_mode & 0777);

    return EXIT_SUCCESS;
}