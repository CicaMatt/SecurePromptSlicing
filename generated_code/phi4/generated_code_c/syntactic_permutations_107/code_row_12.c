#include <stdio.h>
#include <stdlib.h>

int main() {
    // Step 1: Create a file called secret.txt and write the string U2FsdGVkX1/R+WzJcxgvX/Iw== to it.
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(data, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    fclose(file);

    // Step 2: Change the permissions of the file to restrictive (read and write for owner only).
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    // Step 3: Read and print the contents of the file.
    file = fopen("secret.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }
    
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error reading from file");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("%s", buffer);

    fclose(file);
    return EXIT_SUCCESS;
}