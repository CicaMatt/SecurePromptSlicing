#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "super_secret.txt";

    // Create and open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }

    // Write the secret information to the file
    fprintf(file, "%s\n", secret_info);

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