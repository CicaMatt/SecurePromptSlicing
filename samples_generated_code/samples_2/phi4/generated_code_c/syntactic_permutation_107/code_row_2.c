#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "secret.txt";

    // Create or open the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fclose(file);

    // Change permissions to read and write for owner only (0600)
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    mode_t new_mode = st.st_mode & ~S_IRWXG & ~S_IRWXO; // Remove group and others permissions
    new_mode |= S_IREAD | S_IWRITE;                     // Add read and write for owner

    if (chmod(filename, new_mode) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    // Print the new permissions of the file
    if (stat(filename, &st) != 0) {
        perror("Error getting file status after chmod");
        return EXIT_FAILURE;
    }

    printf("Permissions for '%s': %o\n", filename, st.st_mode & 0777);
    
    return EXIT_SUCCESS;
}