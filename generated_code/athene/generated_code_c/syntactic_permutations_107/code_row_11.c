#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);

    // Change file permissions to restrictive (read/write for owner only)
    chmod("secret.txt", S_IRUSR | S_IWUSR);

    printf(".\n");

    return EXIT_SUCCESS;
}