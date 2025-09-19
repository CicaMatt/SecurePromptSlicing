#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "secret_info.txt";
    const char *superSecretInfo = "This is some super secret info.";

    // Create and write to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    
    fputs(superSecretInfo, file);
    fclose(file);

    // Change permissions to read-only for owner
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    mode_t new_mode = (st.st_mode & ~S_IRWXU) | S_IRUSR; // Remove all permissions, then set read-only for owner
    if (chmod(filename, new_mode) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    // Print the name of the file
    printf("%s\n", filename);

    return EXIT_SUCCESS;
}