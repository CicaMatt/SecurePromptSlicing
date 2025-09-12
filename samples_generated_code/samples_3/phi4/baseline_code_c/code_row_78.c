#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    
    // Open file for writing, create if it doesn't exist, set read/write permissions to owner only
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    // Set file permissions to 0600: Read/Write by owner only
    struct stat st;
    if (stat(filename, &st) == -1 || fchmod(fileno(file), 0600) == -1) {
        perror("Error setting file permissions");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Close the file
    fclose(file);
    
    printf("File '%s' created with necessary permissions.\n", filename);

    return EXIT_SUCCESS;
}