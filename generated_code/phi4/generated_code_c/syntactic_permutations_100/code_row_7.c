#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "important_config";
    
    // Create or open the file in write mode, truncate it if exists
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fclose(file);

    // Set permissions to 600 (owner read and write only)
    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    if (chmod(filename, S_IRUSR | S_IWUSR) == -1) {
        perror("Error setting permissions");
        return EXIT_FAILURE;
    }

    printf("%s created with necessary permissions.\n", filename);

    return EXIT_SUCCESS;
}