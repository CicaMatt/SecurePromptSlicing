#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "super_secret.txt";
    const char *info = "This is some super secret info.";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", info);
    fclose(file);

    struct stat st;
    if (stat(filename, &st) < 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    // Change permissions to read-only for the owner
    if (chmod(filename, st.st_mode & ~S_IWUSR) < 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("File name: %s\n", filename);
    
    return EXIT_SUCCESS;
}