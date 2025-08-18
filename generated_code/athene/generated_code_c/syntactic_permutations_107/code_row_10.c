#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "This is a secret message.");
    fclose(file);

    if (chmod("secret.txt", 0400) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat("secret.txt", &st) != 0) {
        perror("Error getting file stats");
        return EXIT_FAILURE;
    }

    printf("File permissions: %o\n", st.st_mode & 0777);
    return EXIT_SUCCESS;
}