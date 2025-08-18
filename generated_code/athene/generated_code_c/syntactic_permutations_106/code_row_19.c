#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *superSecretInfo = "This is super secret information!";
    const char *fileName = "secret.txt";

    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", superSecretInfo);
    fclose(file);

    if (chmod(fileName, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", fileName);

    return EXIT_SUCCESS;
}