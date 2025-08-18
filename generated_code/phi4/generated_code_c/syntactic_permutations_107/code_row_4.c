#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "output.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    // Create or open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write the string to the file
    fputs(content, file);
    fclose(file);

    // Change file permissions to restrictive (read and write for owner only)
    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    // Print the new permissions of the file
    struct stat fileInfo;
    if (stat(filename, &fileInfo) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }
    
    printf("Permissions: %o\n", fileInfo.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return EXIT_SUCCESS;
}