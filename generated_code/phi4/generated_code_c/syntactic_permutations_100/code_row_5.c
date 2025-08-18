#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "important_config";
    
    // Create and open the file with write mode, create if it does not exist
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    // Close the file after creation
    fclose(file);

    // Set the necessary permissions for the file: owner can read and write, others only read (0644)
    struct stat st;
    if (stat(filename, &st) == 0) {
        if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
            perror("Error setting file permissions");
            return EXIT_FAILURE;
        }
    } else {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}