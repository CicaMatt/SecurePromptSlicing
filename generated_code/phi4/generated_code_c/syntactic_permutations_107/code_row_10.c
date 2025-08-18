#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";

    // Create or open the file
    file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Write some content to the file
    fprintf(file, "This is a secret message.\n");

    // Close the file
    fclose(file);

    // Change permissions to restrictive (read/write for owner only)
    if (chmod(filename, S_IRUSR | S_IWUSR) == -1) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    // Retrieve and print the permissions of the file
    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    printf("File Permissions: %o\n", st.st_mode & 0777);

    return 0;
}