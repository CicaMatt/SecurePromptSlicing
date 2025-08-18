#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", content);
    fclose(file);

    chmod(filename, 0400);

    printf(".\n");

    return EXIT_SUCCESS;
}