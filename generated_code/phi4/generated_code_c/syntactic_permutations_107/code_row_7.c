#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "output.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    // Create and write to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fputs(data, file);
    fclose(file);

    // Change file permissions
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Stat error");
        return EXIT_FAILURE;
    }

    mode_t perms = st.st_mode & ~(S_IRWXG | S_IRWXO); // Remove group and other permissions
    if (chmod(filename, perms) != 0) {
        perror("Chmod error");
        return EXIT_FAILURE;
    }

    // Re-check file permissions
    if (stat(filename, &st) != 0) {
        perror("Stat error after chmod");
        return EXIT_FAILURE;
    }

    printf("Permissions of the file: %o\n", st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return EXIT_SUCCESS;
}