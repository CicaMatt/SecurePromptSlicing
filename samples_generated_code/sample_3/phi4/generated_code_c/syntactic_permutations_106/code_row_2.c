#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "super_secret.txt";
    const char *content = "This is some super secret info.";
    
    // Create and write to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s", content);
    fclose(file);

    // Change permissions of the file to read-only for owner
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    // Print the name of the file to the screen
    printf("%s\n", filename);

    return EXIT_SUCCESS;
}