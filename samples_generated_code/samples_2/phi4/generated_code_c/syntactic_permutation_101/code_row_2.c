#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    
    // Open the file in write mode, create it if it doesn't exist
    file = fopen(filename, "w");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write a string to the file
    const char *text = "important_config is opened\n";
    fputs(text, file);
    
    // Close the file
    fclose(file);

    return EXIT_SUCCESS;
}