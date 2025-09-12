#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret = "super secret info";
    const char *filename = "secretfile.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secret);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);
    return EXIT_SUCCESS;
}