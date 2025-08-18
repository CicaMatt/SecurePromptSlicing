#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(content, file) == EOF) {
        perror("Failed to write to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    // Change the permissions of the file to be read-only for owner
    if (chmod("secret.txt", 0600) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}