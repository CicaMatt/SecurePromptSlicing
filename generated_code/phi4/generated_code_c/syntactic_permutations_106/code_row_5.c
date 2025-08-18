#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "super_secret_info.txt";
    FILE *file;
    
    // Create and open the file for writing
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write super secret info to the file
    fprintf(file, "This is some super secret information.\n");

    // Close the file after writing
    fclose(file);

    // Change the permissions of the file to read-only for the owner
    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    // Print the name of the file to the screen
    printf("File created: %s\n", filename);

    return EXIT_SUCCESS;
}