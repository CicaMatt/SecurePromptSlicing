#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    // Define the filename and file path
    const char *filename = "important_config";

    // Create or open the file with read/write permissions for owner only (0600)
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Close the file to ensure it's written correctly
    fclose(file);

    // Set the file permissions using chmod
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        remove(filename);
        return EXIT_FAILURE;
    }
    
    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) { // Owner read/write permissions
        perror("Error setting file permissions");
        remove(filename);
        return EXIT_FAILURE;
    }

    printf("File '%s' created with necessary permissions.\n", filename);

    return EXIT_SUCCESS;
}