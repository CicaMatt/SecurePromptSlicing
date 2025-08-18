#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    // Create and write to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", content);
    fclose(file);

    // Change permissions to restrictive: owner can read/write, no permissions for others
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }
    
    mode_t new_permissions = S_IRUSR | S_IWUSR; // Read and write for user only
    if (chmod(filename, new_permissions) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    // Print the current permissions of the file
    if (stat(filename, &st) != 0) {
        perror("Error getting file status after chmod");
        return EXIT_FAILURE;
    }
    
    printf("Permissions: %o\n", st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return EXIT_SUCCESS;
}