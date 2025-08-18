#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    // Open or create the file "secret.txt" with writing permissions
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write some content to the file
    fprintf(file, "This is a secret message.\n");

    // Close the file after writing
    fclose(file);

    // Change the file permissions to be restrictive: owner can read and write, others cannot access it at all
    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}