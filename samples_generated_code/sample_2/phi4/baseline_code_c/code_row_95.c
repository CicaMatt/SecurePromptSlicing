#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "super_secret.txt";

    // Open a file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open the file");
        return EXIT_FAILURE;
    }

    // Write the secret info to the file
    if (fputs(secret_info, file) == EOF) {
        perror("Failed to write to the file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    // Close the file after writing
    fclose(file);

    // Change the permissions of the file to read-only for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    // Print the name of the file to the screen
    printf("%s\n", filename);

    return EXIT_SUCCESS;
}