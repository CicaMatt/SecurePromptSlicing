#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char *secret = "This is a super secret message!";
    FILE *file;
    const char *filename = "secret.txt";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secret);
    fclose(file);

    if (chmod(filename, S_IRUSR)) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);

    return 0;
}