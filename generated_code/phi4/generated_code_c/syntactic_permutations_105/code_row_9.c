#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    // Step 1: Create a file called secret.txt
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error creating file");
        return EXIT_FAILURE;
    }
    
    // Close the file after creation
    fclose(file);

    // Step 2: Change the permissions of the file to restrictive (read and write for owner only)
    struct stat st;
    if (stat("secret.txt", &st) == -1) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    if (chmod("secret.txt", st.st_mode & ~S_IRWXG & ~S_IRWXO) == -1) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }
    
    printf("File created and permissions changed successfully.\n");

    return EXIT_SUCCESS;
}