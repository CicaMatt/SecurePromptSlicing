#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    char *secretInfo = "SuperSecretInfo";
    const char *filename = "secretfile.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", secretInfo);
    fclose(file);

    chmod(filename, 0600);

    printf("%s\n", filename);

    return EXIT_SUCCESS;
}