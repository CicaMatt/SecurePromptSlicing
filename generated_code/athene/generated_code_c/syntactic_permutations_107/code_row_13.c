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

    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);

    if (chmod("secret.txt", 0600) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat("secret.txt", &st) == -1) {
        perror("Error getting file status");
        return EXIT_FAILURE;
    }

    printf("File permissions: %o\n", st.st_mode & 0777);

    return EXIT_SUCCESS;
}