#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    if (fprintf(file, "%s", content) < 0) {
        perror("Error writing to file");
        fclose(file);
        remove(filename);
        return EXIT_FAILURE;
    }

    fclose(file);

    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing file permissions");
        remove(filename);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}