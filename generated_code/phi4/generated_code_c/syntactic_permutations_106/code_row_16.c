#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secretInfo = "This is some super secret info.";
    const char *filename = "secret.txt";

    // Create and write to file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", secretInfo);
    fclose(file);

    // Change file permissions to read-only for the owner
    struct stat fileStat;
    if (stat(filename, &fileStat) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    if (chmod(filename, fileStat.st_mode & ~S_IWUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    // Print the name of the file
    printf("File created: %s\n", filename);

    return EXIT_SUCCESS;
}