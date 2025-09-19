#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *info = "This is some super secret info.";
    const char *filename = "secret_info.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", info);
    fclose(file);

    struct stat file_stat;
    if (stat(filename, &file_stat) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    if (chmod(filename, file_stat.st_mode & ~S_IWUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    printf("File created and secured: %s\n", filename);

    return EXIT_SUCCESS;
}