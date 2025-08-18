#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *secret = "SuperSecretInfo";
    const char *filename = "secretfile.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", secret);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Error changing file permissions");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", filename);
    return 0;
}