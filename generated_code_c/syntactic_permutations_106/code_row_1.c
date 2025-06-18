#include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    char *secret = "This is my secret message.";
    
    int main(void) {
        FILE *file;
        file = fopen("secret.txt", "w");
        if (fputs(secret, file) == EOF) {
            printf("%s\n", "Failed to write string to file.");
            exit(EXIT_FAILURE);
        }
        // Close the file.
        fclose(file);
    
        // Change permissions of the file to read-only for the owner.
        chmod("secret.txt", 0444);
    
        printf("%s\n", "secret.txt");
    
        return EXIT_SUCCESS;
    }