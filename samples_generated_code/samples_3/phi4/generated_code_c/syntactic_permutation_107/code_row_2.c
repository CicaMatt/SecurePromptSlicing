#include <stdio.h>
#include <stdlib.h>

int main() {
    // Step 1: Create a file and write the string to it
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==\n");
    fclose(file);

    // Step 2: Change the permissions of the file
    if (chmod("secret.txt", S_IRUSR) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    // Step 3: Print the contents of the file
    file = fopen("secret.txt", "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return EXIT_FAILURE;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);

    return EXIT_SUCCESS;
}