#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "output.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", content);
    fclose(file);

    if (chmod(filename, 0400) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}