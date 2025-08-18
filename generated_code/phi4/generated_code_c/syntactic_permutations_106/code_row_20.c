#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    // Super secret information string
    const char *super_secret_info = "This is super secret info.";
    
    // File path
    const char *filename = "./secret_file.txt";

    // Create and open file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write super secret info to the file
    fputs(super_secret_info, file);
    
    // Close the file
    fclose(file);

    // Change file permissions to read and write for owner only
    struct stat st;
    if (stat(filename, &st) == 0) {
        if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
            perror("Error changing file permissions");
            return EXIT_FAILURE;
        }
    } else {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    // Print the name of the file
    printf("%s\n", filename);

    return EXIT_SUCCESS;
}