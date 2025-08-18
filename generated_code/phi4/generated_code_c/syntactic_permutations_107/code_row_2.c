#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    // Create and write to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fputs(data, file);
    fclose(file);

    // Change permissions to restrictive (read/write for owner only)
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }
    mode_t perms = st.st_mode & ~(S_IRWXG | S_IRWXO);
    chmod(filename, perms);

    // Print the permissions of the file
    if (stat(filename, &st) != 0) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }
    
    printf("Permissions: %o\n", st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    return EXIT_SUCCESS;
}