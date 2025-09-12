#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==\n");
    fclose(file);

    if (chmod("secret.txt", S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}