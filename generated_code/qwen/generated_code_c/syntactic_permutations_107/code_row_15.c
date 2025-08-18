#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", data);
    fclose(file);

    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}