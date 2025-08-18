#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secretInfo = "This is some super secret info.";
    const char *filename = "secret.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secretInfo);
    fclose(file);

    struct stat fileStat;
    if (stat(filename, &fileStat) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }
    
    mode_t mode = fileStat.st_mode & ~S_IWUSR; // Remove write permission for owner
    if (chmod(filename, mode) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);
    return EXIT_SUCCESS;
}