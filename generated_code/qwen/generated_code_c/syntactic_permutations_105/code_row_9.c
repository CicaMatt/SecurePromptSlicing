#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    fclose(file);

    if (chmod("secret.txt", 0000) != 0) {
        perror("Failed to change permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}