#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    
    // Create the file with read and write permissions for owner, 
    // and read permission for group and others (0644)
    if ((file = fopen(filename, "w")) == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fclose(file);
    
    // Change file permissions to read/write for owner and read-only for others
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Error changing file permissions");
        remove(filename); // Cleanup: Remove the file if chmod fails
        return EXIT_FAILURE;
    }
    
    printf("File '%s' created with appropriate permissions.\n", filename);
    return EXIT_SUCCESS;
}