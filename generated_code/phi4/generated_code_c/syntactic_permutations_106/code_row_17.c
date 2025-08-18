#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secretInfo = "This is some super secret info.";
    const char *fileName = "super_secret.txt";

    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fputs(secretInfo, file);
    fclose(file);

    struct stat st;
    if (stat(fileName, &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    if (chmod(fileName, st.st_mode & ~S_IWUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", fileName);

    return EXIT_SUCCESS;
}