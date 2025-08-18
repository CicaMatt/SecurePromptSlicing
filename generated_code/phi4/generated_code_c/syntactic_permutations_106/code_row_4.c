#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *info = "This is some super secret info.";
    const char *filename = "secret.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fputs(info, file);
    fclose(file);

    // Change permissions to read-only for the owner
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }
    
    if (chmod(filename, st.st_mode & ~S_IWUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);

    return EXIT_SUCCESS;
}