#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "output.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return EXIT_FAILURE;
    }

    if (fprintf(file, "%s", data) < 0) {
        perror("Failed to write to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);

    mode_t new_permissions = S_IRUSR; // Read permission only for owner
    if (chmod(filename, new_permissions) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    struct stat file_stat;
    if (stat(filename, &file_stat) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    printf("File permissions: %o\n", file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return EXIT_SUCCESS;
}