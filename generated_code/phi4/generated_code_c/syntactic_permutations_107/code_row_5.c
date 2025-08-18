#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    // Create and write the content to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "%s", content);
    fclose(file);

    // Change permissions of the file to read-only for owner (0600)
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Error getting file status");
        return 1;
    }

    // Check current permissions
    printf("Original Permissions: %o\n", st.st_mode & 0777);

    if (chmod(filename, 0600) != 0) {
        perror("Error changing file permissions");
        return 1;
    }

    // Verify new permissions
    if (stat(filename, &st) != 0) {
        perror("Error getting file status after chmod");
        return 1;
    }
    
    printf("New Permissions: %o\n", st.st_mode & 0777);

    return 0;
}