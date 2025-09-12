#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    // Define the super secret info string
    const char *secretInfo = "This is some super secret information.";
    
    // Specify the file name
    const char *fileName = "super_secret.txt";
    
    // Open or create the file for writing
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    
    // Write the super secret info to the file
    fprintf(file, "%s", secretInfo);
    
    // Close the file
    fclose(file);
    
    // Change the permissions to read-only for the owner
    if (chmod(fileName, S_IRUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }
    
    // Print the name of the file to the screen
    printf("%s\n", fileName);
    
    return EXIT_SUCCESS;
}