#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "secret.txt";
    const char *secret_info = "This is super secret info.";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    if (chmod(filename, 0400) != 0) {
        perror("Error changing permissions");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", filename);

    return 0;
}