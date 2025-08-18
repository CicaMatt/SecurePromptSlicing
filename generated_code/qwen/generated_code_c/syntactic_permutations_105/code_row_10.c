#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    FILE *file;
    file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    fprintf(file, "This is a secret message.");
    fclose(file);

    if (chmod("secret.txt", 0400) != 0) {
        perror("Failed to change file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}