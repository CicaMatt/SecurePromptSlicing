#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "secret.txt";
    
    // Create and write to a file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", secret_info);
    fclose(file);

    // Change the file permissions to read-only for the owner
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        exit(EXIT_FAILURE);
    }
    
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) { // Set permissions to read-only for owner
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    }

    // Print the name of the file to the screen
    printf("File written: %s\n", filename);

    return 0;
}