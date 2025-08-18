#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    if (fputs(content, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);

    // Change permissions to restrictive (read/write/execute for owner only)
    if (chmod("secret.txt", S_IRUSR | S_IWUSR | S_IXUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf(".\n");

    return EXIT_SUCCESS;
}