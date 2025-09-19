#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fprintf(file, "%s\n", data);
    fclose(file);

    // Change the permissions of the file to read and write for owner only
    if (chmod("secret.txt", 0600) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf("File created and permissions changed successfully.\n");

    return EXIT_SUCCESS;
}