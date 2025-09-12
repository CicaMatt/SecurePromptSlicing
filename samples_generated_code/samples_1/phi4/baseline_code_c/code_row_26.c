#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    
    // Create and open the file "important_config" with write access.
    // If the file does not exist, it will be created; if it exists, its contents will be overwritten.
    file = fopen("important_config", "w");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    // Close the file to ensure data is written and resources are released
    fclose(file);
    
    // Set necessary permissions on Unix-like systems (Linux, macOS)
    // This sets read/write/execute for owner, and read/execute for group and others.
    if (chmod("important_config", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0) {
        perror("Error setting file permissions");
        return EXIT_FAILURE;
    }
    
    printf("File 'important_config' created and permissions set successfully.\n");

    return EXIT_SUCCESS;
}