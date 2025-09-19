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

    fputs(secret_info, file);
    fclose(file);

    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }
    
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "Not a regular file\n");
        return EXIT_FAILURE;
    }

    st.st_mode &= ~S_IWUSR; // Remove write permission for the owner
    if (chmod(filename, st.st_mode) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("File name: %s\n", filename);

    return EXIT_SUCCESS;
}